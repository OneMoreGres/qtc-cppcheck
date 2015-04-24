#include <QDebug>
#include <QSettings>
#include <QFileInfo>
#include <QDir>
#include <QThread>

#include <coreplugin/messagemanager.h>
#include <coreplugin/progressmanager/progressmanager.h>
#include <coreplugin/progressmanager/futureprogress.h>

#include "CppcheckRunner.h"
#include "Constants.h"
#include "Settings.h"

using namespace QtcCppcheck::Internal;

namespace
{
  enum ErrorField
  {
    ErrorFieldFile = 0, ErrorFieldLine, ErrorFieldSeverity, ErrorFieldId,
    ErrorFieldMessage
  };

  QStringList includePaths (const QStringList& files)
  {
    QStringList paths;
    foreach (const QString& file, files)
    {
      QFileInfo info (file);
      QString current = QString (QLatin1String("-I")) + info.absolutePath ();
      if (!paths.contains(current))
      {
        paths << current;
      }
    }
    return paths;
  }

}

CppcheckRunner::CppcheckRunner(Settings *settings, QObject *parent) :
  QObject(parent), settings_ (settings), showOutput_ (false), futureInterface_ (NULL)
{
  Q_ASSERT (settings_ != NULL);

  connect (&process_, SIGNAL (readyReadStandardOutput()),
           SLOT (readOutput()));
  connect (&process_, SIGNAL (readyReadStandardError()),
           SLOT (readError()));
  connect (&process_, SIGNAL (started()),
           SLOT (started()));
  connect (&process_, SIGNAL (error(QProcess::ProcessError)),
           SLOT (error(QProcess::ProcessError)));
  connect (&process_, SIGNAL (finished(int, QProcess::ExitStatus)),
           SLOT (finished(int, QProcess::ExitStatus)));

  // Restart checking if got queue.
  connect (&process_, SIGNAL (finished(int, QProcess::ExitStatus)),
           SLOT (checkQueuedFiles ()));
}

CppcheckRunner::~CppcheckRunner()
{
  if (process_.isOpen())
  {
    process_.kill();
  }
  queueTimer_.stop ();
  settings_ = NULL;
  delete futureInterface_;
}

void CppcheckRunner::updateSettings()
{
  Q_ASSERT (settings_ != NULL);
  showOutput_ = settings_->showBinaryOutput ();
  runArguments_.clear ();
  // Pass custom params BEFORE most of runner's to shadow if some repeat.
  runArguments_ += settings_->customParameters ().split (
                     QLatin1Char (' '), QString::SkipEmptyParts);
  QString enabled = QLatin1String ("--enable=warning,style,performance,"
                                   "portability,information,missingInclude");
  // Overwrite enable with user parameters if present
  for(int i = runArguments_.size () - 1; i >= 0; --i)
  {
    if (runArguments_.at (i).startsWith (QLatin1String ("--enable")))
    {
      enabled = runArguments_.takeAt (i);
      break;
    }
  }
  if (settings_->checkUnused ())
  {
    enabled += QLatin1String (",unusedFunction");
  }
  else //TODO always check with threads but rescan for unused after finish?
  {
    runArguments_ << (QLatin1String ("-j ") +
                      QString::number (QThread::idealThreadCount ()));
  }
  runArguments_ << enabled;
  if (settings_->checkInconclusive ())
  {
    runArguments_ << QLatin1String ("--inconclusive");
  }
  runArguments_ << QLatin1String ("--template={file},{line},{severity},{id},{message}");
}

void CppcheckRunner::checkFiles(const QStringList &fileNames)
{
  Q_ASSERT (!fileNames.isEmpty ());
  fileCheckQueue_ += fileNames;
  fileCheckQueue_.removeDuplicates ();
  fileCheckQueue_.sort ();
  if (process_.isOpen ())
  {
    if (fileCheckQueue_ == currentlyCheckingFiles_)
    {
      process_.kill ();
      // Rechecking will be restarted on finish signal.
    }
    return;
  }
  // Delay helps to avoid double checking same file on editor change.
  const int checkDelayInMs = 200;
  if (!queueTimer_.isActive ())
  {
    queueTimer_.singleShot (checkDelayInMs, this, SLOT (checkQueuedFiles ()));
  }
}

void CppcheckRunner::stopChecking()
{
  fileCheckQueue_.clear ();
  if (process_.isOpen ())
  {
    process_.kill ();
  }
}

void CppcheckRunner::checkQueuedFiles()
{
  if (fileCheckQueue_.isEmpty ())
  {
    return;
  }
  QString binary = settings_->binaryFile ();
  if (binary.isEmpty ())
  {
    return;
  }
  QStringList arguments (runArguments_);
  arguments += includePaths (fileCheckQueue_);
  arguments += fileCheckQueue_;
  currentlyCheckingFiles_ = fileCheckQueue_;
  fileCheckQueue_.clear ();
  emit startedChecking (currentlyCheckingFiles_);
  process_.start (binary, arguments);
}

void CppcheckRunner::readOutput()
{
  if (!showOutput_)
  {
    return;
  }
  process_.setReadChannel (QProcess::StandardOutput);

  while (!process_.atEnd ())
  {
    QByteArray rawLine = process_.readLine ();
    QString line = QString::fromUtf8 (rawLine).trimmed ();
    if (line.isEmpty ())
    {
      continue;
    }
    const QString progressSample = QLatin1String ("% done");
    // check futureInterface because read can be triggered before started..
    if (line.endsWith (progressSample) && futureInterface_ != NULL)
    {
      int percentEndIndex = line.length () - progressSample.length ();
      int percentStartIndex = line.lastIndexOf(QLatin1String (" "), percentEndIndex);
      int done = line.mid (percentStartIndex, percentEndIndex - percentStartIndex).toInt ();
      futureInterface_->setProgressValue (done);
    }
    Core::MessageManager::write (line, Core::MessageManager::Silent);
  }
}

void CppcheckRunner::readError()
{
  process_.setReadChannel (QProcess::StandardError);

  while (!process_.atEnd ())
  {
    QByteArray rawLine = process_.readLine ();
    QString line = QString::fromUtf8 (rawLine).trimmed ();
    if (line.isEmpty ())
    {
      continue;
    }
    if (showOutput_)
    {
      Core::MessageManager::write (line, Core::MessageManager::Silent);
    }
    QStringList details = line.split (QLatin1Char (','));
    if (details.size () <= ErrorFieldMessage)
    {
      continue;
    }
    QString file = QDir::fromNativeSeparators(details.at (ErrorFieldFile));
    int lineNumber = details.at (ErrorFieldLine).toInt ();
    char type = details.at (ErrorFieldSeverity).at (0).toLatin1 ();
    QString description = line.mid (line.indexOf (details.at (ErrorFieldMessage)));
    emit newTask (type, description, file, lineNumber);
  }
}

void CppcheckRunner::started()
{
  if (showOutput_)
  {
    Core::MessageManager::write (tr ("Cppcheck started"), Core::MessageManager::Silent);
  }

  using namespace Core;
  delete futureInterface_;
  futureInterface_ = new QFutureInterface<void>;
  FutureProgress *progress = ProgressManager::addTask(futureInterface_->future(),
                                                      tr("Cppcheck"), Constants::TASK_CHECKING);
  connect (progress, SIGNAL(canceled ()), SLOT(stopChecking ()));
  futureInterface_->setProgressRange(0, 100); // %
  futureInterface_->reportStarted();
}

void CppcheckRunner::error(QProcess::ProcessError error)
{
  Q_UNUSED (error);
  if (showOutput_)
  {
    Core::MessageManager::write (tr ("Cppcheck error occured"), Core::MessageManager::Silent);
  }
}

void CppcheckRunner::finished(int exitCode, QProcess::ExitStatus exitStatus)
{
  Q_UNUSED (exitCode);
  Q_UNUSED (exitStatus);
  Q_ASSERT (futureInterface_ != NULL);
  futureInterface_->reportFinished ();
  process_.close ();
  if (showOutput_)
  {
    Core::MessageManager::write (tr("Cppcheck finished"), Core::MessageManager::Silent);
  }
}
