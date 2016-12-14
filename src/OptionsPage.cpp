#include <QPointer>
#include <QCoreApplication>

#include "OptionsPage.h"
#include "OptionsWidget.h"
#include "Constants.h"

using namespace QtcCppcheck::Internal;

OptionsPage::OptionsPage(Settings *settings, QObject *parent) :
  IOptionsPage(parent), settings_ (settings)
{
  Q_ASSERT (settings_ != NULL);
  setId (Constants::OPTIONS_PAGE_ID);
  setDisplayName (tr ("QtcCppcheck"));
  setCategory(Constants::OPTIONS_CATEGORY_ID);
  setDisplayCategory(QCoreApplication::translate("Analyzer", "Analyzer"));
  setCategoryIcon(Utils::Icon (Constants::OPTIONS_CATEGORY_ICON));

  keyWords_ << QLatin1String ("cppcheck");
}

OptionsPage::~OptionsPage()
{
  settings_ = NULL;
}

bool OptionsPage::matches(const QString &searchKeyWord) const
{
  return keyWords_.contains (searchKeyWord);
}

QWidget *OptionsPage::widget()
{
  return createPage (NULL);
}

QWidget *OptionsPage::createPage(QWidget *parent)
{
  Q_ASSERT (settings_ != NULL);
  widget_ = new OptionsWidget (settings_, parent);
  Q_CHECK_PTR (widget_.data ());
  return widget_.data ();
}

void OptionsPage::apply()
{
  Q_ASSERT (!widget_.isNull ());
  widget_->applySettings ();
  emit settingsChanged ();
}

void OptionsPage::finish()
{

}
