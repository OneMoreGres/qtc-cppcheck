DEFINES += QTCCPPCHECK_LIBRARY

VERSION_SUFFIX = ""

include(paths.pri)

# QtcCppcheck files

SOURCES += \
    src/OptionsWidget.cpp \
    src/OptionsPage.cpp \
    src/CppcheckRunner.cpp \
    src/Settings.cpp \
    src/TaskInfo.cpp \
    src/QtcCppcheckPlugin.cpp

HEADERS += \
    src/OptionsWidget.h \
    src/OptionsPage.h \
    src/CppcheckRunner.h \
    src/Settings.h \
    src/Constants.h \
    src/PluginGlobal.h \
    src/TaskInfo.h \
    src/QtcCppcheckPlugin.h

FORMS += \
    src/OptionsWidget.ui

TRANSLATIONS += \
    translation/QtcCppcheck_ru.ts

OTHER_FILES += \
    LICENSE.md \
    README.md \
    util/README.md

PROVIDER = Gres

###### If the plugin can be depended upon by other plugins, this code needs to be outsourced to
###### <dirname>_dependencies.pri, where <dirname> is the name of the directory containing the
###### plugin's sources.

QTC_PLUGIN_NAME = QtcCppcheck
QTC_LIB_DEPENDS += \
    # nothing here at this time

QTC_PLUGIN_DEPENDS += \
    coreplugin\
    projectexplorer

QTC_PLUGIN_RECOMMENDS += \
    # optional plugin dependencies. nothing here at this time

###### End _dependencies.pri contents ######

include($$QTCREATOR_SOURCES/src/qtcreatorplugin.pri)

