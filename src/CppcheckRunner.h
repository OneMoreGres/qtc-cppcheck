#ifndef CPPCHECKRUNNER_H
#define CPPCHECKRUNNER_H

#include <QProcess>
#include <QTimer>
#include <QTemporaryFile>

#include <QFuture>

namespace QtcCppcheck {
  namespace Internal {

    class Settings;

    /*!
     * \brief Cppcheck binary runner.
     *  Does not have ownership on settings_ (must be destroyed before settings).
     * Launches, finishes, reads result, passes start arguments, etc.
     */
    class CppcheckRunner : public QObject
    {
        Q_OBJECT
      public:
        explicit CppcheckRunner(Settings* settings, QObject *parent = 0);
        ~CppcheckRunner ();

        //! Add files to check queue.
        void checkFiles (const QStringList& fileNames);

        //! Update data based on current settings_.
        void updateSettings ();

      public slots:
        //! Stop check progress if running and clear check queue.
        void stopChecking ();

      signals:
        //! New task has been generated.
        void newTask (char type, const QString &description,
                      const QString& fileName, int line);
        //! Inform about starting checking specified files.
        void startedChecking (const QStringList& files);

      private slots:
        //! Check files from queue.
        void checkQueuedFiles ();

        // QProcess handling.
        void readOutput ();
        void readError ();
        void started ();
        void error (QProcess::ProcessError error);
        void finished (int exitCode, QProcess::ExitStatus exitStatus);

      private:
        //! Timer to delay queue checking.
        QTimer queueTimer_;
        //! Binary runner.
        QProcess process_;
        //! Plugin's settings.
        Settings* settings_;
        //! Binary run arguments.
        QStringList runArguments_;
        //! Queued list of files to check.
        QStringList fileCheckQueue_;
        //! List of files currently being checked.
        QStringList currentlyCheckingFiles_;
        //! Should print process' output to MessageManager or not.
        bool showOutput_;
        //! Interface to inform about checking.
        QFutureInterface<void> *futureInterface_;
        //! Max summary arguments length.
        int maxArgumentsLength_;
        //! Current file names in fileListFile_.
        QStringList fileListFileContents_;
        //! File that contains files to check (if there are too much run args).
        QTemporaryFile fileListFile_;
        //! File that contains include paths list (if there are too much run args).
        QTemporaryFile includeListFile_;
    };

  } // namespace Internal
} // namespace QtcCppcheck


#endif // CPPCHECKRUNNER_H
