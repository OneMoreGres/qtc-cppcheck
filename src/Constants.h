#ifndef QTCCPPCHECKCONSTANTS_H
#define QTCCPPCHECKCONSTANTS_H

namespace QtcCppcheck {
  namespace Constants {

    const char OPTIONS_PAGE_ID[] = "QtcCppcheck.OptionsPage";
    const char OPTIONS_CATEGORY_ID[] = "T.Analyzer"; // from valgrind
    const char OPTIONS_CATEGORY_ICON[] = ":/images/analyzer_category.png"; // from valgrind

    const char SETTINGS_GROUP[] = "QtcCppcheck";
    const char SETTINGS_BINARY_FILE[] = "binaryFile";
    const char SETTINGS_CHECK_ON_BUILD[] = "checkOnBuild";
    const char SETTINGS_CHECK_ON_SAVE[] = "checkOnSave";
    const char SETTINGS_CHECK_ON_PROJECT_CHANGE[] = "checkOnProjectChange";
    const char SETTINGS_CHECK_ON_FILE_ADD[] = "checkOnFileAdd";
    const char SETTINGS_CHECK_UNUSED[] = "checkUnused";
    const char SETTINGS_CHECK_INCONCLUSIVE[] = "checkInconclusive";
    const char SETTINGS_CUSTOM_PARAMS[] = "customParams";
    const char SETTINGS_SHOW_OUTPUT[] = "showOutput";
    const char SETTINGS_POPUP_ON_ERROR[] = "popupOnError";
    const char SETTINGS_POPUP_ON_WARNING[] = "popupOnWarning";

    const char TASK_CATEGORY_ID[] = "QtcCppcheck.TaskCategory";
    const char TASK_CATEGORY_NAME[] = "Cppcheck";

    const char TASK_CHECKING[] = "Cppcheck.Task.Checking";

    const char MENU_ID[] = "Cppcheck.Menu";
    const char ACTION_CHECK_NODE_ID[] = "Cppcheck.CheckCurrentNode";
    const char ACTION_CHECK_PROJECT_ID[] = "Cppcheck.CheckActiveProject";
    const char ACTION_CHECK_DOCUMENT_ID[] = "Cppcheck.CheckCurrentDocument";

  } // namespace QtcCppcheck
} // namespace Constants

#endif // QTCCPPCHECKCONSTANTS_H

