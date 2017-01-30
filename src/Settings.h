#ifndef SETTINGS_H
#define SETTINGS_H

#include <QStringList>

namespace QtcCppcheck {
  namespace Internal {

    /*!
     * \brief Plugin's settings.
     * Keeps actual settings.
     * Saves settings in Core::ICore::settings ().
     */
    class Settings
    {
      public:
        explicit Settings(bool autoLoad = false);

        void save ();
        void load ();

        QString binaryFile() const;
        void setBinaryFile(const QString &binaryFile);

        bool checkOnBuild() const;
        void setCheckOnBuild(bool checkOnBuild);

        bool checkOnSave() const;
        void setCheckOnSave(bool checkOnSave);

        bool checkOnProjectChange() const;
        void setCheckOnProjectChange(bool checkOnProjectChange);

        bool checkOnFileAdd() const;
        void setCheckOnFileAdd(bool checkOnFileAdd);

        bool checkUnused() const;
        void setCheckUnused(bool checkUnused);

        bool checkInconclusive() const;
        void setCheckInconclusive(bool checkInconclusive);

        QString customParameters() const;
        void setCustomParameters(const QString &customParameters);

        bool showBinaryOutput() const;
        void setShowBinaryOutput(bool showBinaryOutput);

        bool showId() const;
        void setShowId(bool showId);

        bool popupOnError() const;
        void setPopupOnError(bool popupOnError);

        bool popupOnWarning() const;
        void setPopupOnWarning(bool popupOnWarning);

        QStringList ignorePatterns() const;
        void setIgnorePatterns(const QStringList &ignorePatterns);

    private:
        QString binaryFile_;

        bool checkOnBuild_;
        bool checkOnSave_;
        bool checkOnProjectChange_;
        bool checkOnFileAdd_;

        bool checkUnused_;
        bool checkInconclusive_;
        QString customParameters_;
        QStringList ignorePatterns_;
        bool showBinaryOutput_;
        bool showId_;

        bool popupOnError_;
        bool popupOnWarning_;
    };

  } // namespace Internal
} // namespace QtcCppcheck


#endif // SETTINGS_H
