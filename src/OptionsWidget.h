#ifndef OPTIONSWIDGET_H
#define OPTIONSWIDGET_H

#include <QWidget>
#include <QProcess>

namespace Ui {
  class OptionsWidget;
}

namespace QtcCppcheck {
  namespace Internal {
    class Settings;

    /*!
     * \brief Widget in Options page to edit plugin's settings.
     * Keeps actual settings in settings_. Updates them in applySettings().
     * Does not have ownership on settings_ (options widget begin destroyed before settings).
     * Reads settings and inits self interface in initInterface() on creation.
     */
    class OptionsWidget : public QWidget
    {
        Q_OBJECT

      public:
        explicit OptionsWidget(Settings* settings, QWidget *parent = 0);
        ~OptionsWidget();

        void applySettings ();

      private slots:
        void selectBinaryFile ();
        void getPossibleParams ();

        void finished ();

      private:
        void initInterface ();
        void getVersion ();

      private:
        Ui::OptionsWidget *ui;
        Settings* settings_;
        QProcess process_;
        QStringList processArguments_; // Qt 4 compatibility
    };

  } // namespace Internal
} // namespace QtcCppcheck


#endif // OPTIONSWIDGET_H
