#ifndef OPTIONSPAGE_H
#define OPTIONSPAGE_H

#include <coreplugin/dialogs/ioptionspage.h>
#include <QPointer>

namespace QtcCppcheck {
  namespace Internal {

    class Settings;
    class OptionsWidget;

    /*!
     * \brief Options page.
     * Creates edition widget. Emits settingsChanged().
     */
    class OptionsPage : public Core::IOptionsPage
    {
        Q_OBJECT
      public:
        explicit OptionsPage(Settings* settings, QObject *parent = 0);
        ~OptionsPage ();

        bool matches(const QString &searchKeyWord) const;
        QWidget *widget();
        QWidget *createPage(QWidget *parent);
        void apply();
        void finish();

      signals:
        void settingsChanged ();

      private:
        QPointer<OptionsWidget> widget_;
        Settings* settings_;
        QStringList keyWords_;

    };

  } // namespace Internal
} // namespace QtcCppcheck


#endif // OPTIONSPAGE_H
