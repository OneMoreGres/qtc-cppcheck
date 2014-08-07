QTCREATOR_VERSION = 3.0.1

## set the QTC_SOURCE environment variable to override the setting here
QTCREATOR_SOURCES = $$(QTC_SOURCE)
isEmpty(QTCREATOR_SOURCES):QTCREATOR_SOURCES=C:/Projects/qt-creator/$$QTCREATOR_VERSION/src

## set the QTC_BUILD environment variable to override the setting here
IDE_BUILD_TREE = $$(QTC_BUILD)
isEmpty(IDE_BUILD_TREE){
  msvc{
    IDE_BUILD_TREE=c:/Projects/qt-creator/$$QTCREATOR_VERSION/qtcreator-$$QT_VERSION-vc10
    Release:IDE_BUILD_TREE=$$IDE_BUILD_TREE-release
  }
  else{
    IDE_BUILD_TREE=c:/Projects/qt-creator/$$QTCREATOR_VERSION/qtcreator-$$QT_VERSION
    Release:IDE_BUILD_TREE=$$IDE_BUILD_TREE-release
  }
}
