#include <QString>

#include <coreplugin/icore.h>

#include "Settings.h"
#include "Constants.h"

using namespace QtcCppcheck::Constants;
using namespace QtcCppcheck::Internal;

Settings::Settings(bool autoLoad) :
  checkOnBuild_ (false), checkOnSave_ (false),
  checkOnProjectChange_ (false), checkOnFileAdd_ (false),
  checkUnused_ (false), checkInconclusive_ (false),
  showBinaryOutput_ (false),
  showId_ (false),
  popupOnError_ (false), popupOnWarning_ (false)
{
  if (autoLoad)
  {
    load ();
  }
}

void Settings::save()
{
  Q_ASSERT (Core::ICore::settings () != NULL);
  QSettings& settings = *(Core::ICore::settings ());
  settings.beginGroup (QLatin1String (SETTINGS_GROUP));
  settings.setValue (QLatin1String (SETTINGS_BINARY_FILE), binaryFile_);
  settings.setValue (QLatin1String (SETTINGS_CHECK_ON_BUILD), checkOnBuild_);
  settings.setValue (QLatin1String (SETTINGS_CHECK_ON_SAVE), checkOnSave_);
  settings.setValue (QLatin1String (SETTINGS_CHECK_ON_PROJECT_CHANGE), checkOnProjectChange_);
  settings.setValue (QLatin1String (SETTINGS_CHECK_ON_FILE_ADD), checkOnFileAdd_);
  settings.setValue (QLatin1String (SETTINGS_CHECK_UNUSED), checkUnused_);
  settings.setValue (QLatin1String (SETTINGS_CHECK_INCONCLUSIVE), checkInconclusive_);
  settings.setValue (QLatin1String (SETTINGS_CUSTOM_PARAMS), customParameters_);
  settings.setValue (QLatin1String (SETTINGS_IGNORE_PATTERNS), ignorePatterns_.join (","));
  settings.setValue (QLatin1String (SETTINGS_SHOW_OUTPUT), showBinaryOutput_);
  settings.setValue (QLatin1String (SETTINGS_SHOW_ID), showId_);
  settings.setValue (QLatin1String (SETTINGS_POPUP_ON_ERROR), popupOnError_);
  settings.setValue (QLatin1String (SETTINGS_POPUP_ON_WARNING), popupOnWarning_);
  settings.endGroup ();
}

void Settings::load()
{
  Q_ASSERT (Core::ICore::settings () != NULL);
  QSettings& settings = *(Core::ICore::settings ());
  settings.beginGroup (QLatin1String (SETTINGS_GROUP));
  binaryFile_ = settings.value (QLatin1String (SETTINGS_BINARY_FILE),
                                QString ()).toString ();
  checkOnBuild_ = settings.value (QLatin1String (SETTINGS_CHECK_ON_BUILD),
                                  false).toBool ();
  checkOnSave_ = settings.value (QLatin1String (SETTINGS_CHECK_ON_SAVE),
                                 false).toBool ();
  checkOnProjectChange_ = settings.value (QLatin1String (SETTINGS_CHECK_ON_PROJECT_CHANGE),
                                          false).toBool ();
  checkOnFileAdd_ = settings.value (QLatin1String (SETTINGS_CHECK_ON_FILE_ADD),
                                    false).toBool ();
  checkUnused_ = settings.value (QLatin1String (SETTINGS_CHECK_UNUSED),
                                 false).toBool ();
  checkInconclusive_ = settings.value (QLatin1String (SETTINGS_CHECK_INCONCLUSIVE),
                                       false).toBool ();
  customParameters_ = settings.value (QLatin1String (SETTINGS_CUSTOM_PARAMS),
                                      QString ()).toString ();
  ignorePatterns_ = settings.value (QLatin1String (SETTINGS_IGNORE_PATTERNS),
                                    QString ()).toString ().split (",", QString::SkipEmptyParts);
  showBinaryOutput_ = settings.value (QLatin1String (SETTINGS_SHOW_OUTPUT),
                                      false).toBool ();
  showId_ = settings.value (QLatin1String (SETTINGS_SHOW_ID),
                                      false).toBool ();
  popupOnError_ = settings.value (QLatin1String (SETTINGS_POPUP_ON_ERROR),
                                      true).toBool ();
  popupOnWarning_ = settings.value (QLatin1String (SETTINGS_POPUP_ON_WARNING),
                                      true).toBool ();
  settings.endGroup ();
}

QString Settings::binaryFile() const
{
  return binaryFile_;
}

void Settings::setBinaryFile(const QString &binaryFile)
{
  binaryFile_ = binaryFile;
}

bool Settings::checkOnBuild() const
{
  return checkOnBuild_;
}

void Settings::setCheckOnBuild(bool checkOnBuild)
{
  checkOnBuild_ = checkOnBuild;
}

bool Settings::checkInconclusive() const
{
  return checkInconclusive_;
}

void Settings::setCheckInconclusive(bool checkInconclusive)
{
  checkInconclusive_ = checkInconclusive;
}

QString Settings::customParameters() const
{
  return customParameters_;
}

void Settings::setCustomParameters(const QString &customParameters)
{
  customParameters_ = customParameters;
}

bool Settings::showBinaryOutput() const
{
  return showBinaryOutput_;
}

void Settings::setShowBinaryOutput(bool showBinaryOutput)
{
  showBinaryOutput_ = showBinaryOutput;
}

bool Settings::showId() const
{
  return showId_;
}

void Settings::setShowId(bool showId)
{
  showId_ = showId;
}

bool Settings::popupOnError() const
{
  return popupOnError_;
}

void Settings::setPopupOnError(bool popupOnError)
{
  popupOnError_ = popupOnError;
}
bool Settings::popupOnWarning() const
{
  return popupOnWarning_;
}

void Settings::setPopupOnWarning(bool popupOnWarning)
{
  popupOnWarning_ = popupOnWarning;
}

QStringList Settings::ignorePatterns() const
{
  return ignorePatterns_;
}

void Settings::setIgnorePatterns(const QStringList &ignorePatterns)
{
  ignorePatterns_ = ignorePatterns;
  for (auto& i: ignorePatterns_)
  {
    i = i.trimmed () ;
  }
}

bool Settings::checkOnProjectChange() const
{
  return checkOnProjectChange_;
}

void Settings::setCheckOnProjectChange(bool checkOnProjectChange)
{
  checkOnProjectChange_ = checkOnProjectChange;
}

bool Settings::checkOnFileAdd() const
{
  return checkOnFileAdd_;
}

void Settings::setCheckOnFileAdd(bool checkOnFileAdd)
{
  checkOnFileAdd_ = checkOnFileAdd;
}

bool Settings::checkUnused() const
{
  return checkUnused_;
}

void Settings::setCheckUnused(bool checkUnused)
{
  checkUnused_ = checkUnused;
}

bool Settings::checkOnSave() const
{
  return checkOnSave_;
}

void Settings::setCheckOnSave(bool checkOnSave)
{
  checkOnSave_ = checkOnSave;
}



