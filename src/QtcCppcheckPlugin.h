#ifndef QTCCPPCHECK_H
#define QTCCPPCHECK_H

#include "PluginGlobal.h"
#include <QModelIndex>
#include <QStringList>
#include <QPointer>

#include <extensionsystem/iplugin.h>

namespace ProjectExplorer
{
  class Project;
  class Task;
  class Node;
}
namespace Core
{
  class IDocument;
}

namespace QtcCppcheck {
  namespace Internal {

    class Settings;
    class CppcheckRunner;
    class TaskInfo;

    /*!
     * \brief main plugin class.
     * Holds Settings and CppcheckRunner objects.
     * Determines when to check files/projects.
     * Adds/removes tasks from project explorer.
     */
    class QtcCppcheckPlugin : public ExtensionSystem::IPlugin
    {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "QtcCppcheck.json")

      public:
        QtcCppcheckPlugin();
        ~QtcCppcheckPlugin();

        bool initialize(const QStringList &arguments, QString *errorString);
        void extensionsInitialized();
        ShutdownFlag aboutToShutdown();

      private slots:
        // General checking.
        //! Check active project.
        void checkActiveProject ();
        //! Check currently open document.
        void checkCurrentDocument ();
        //! Check current ProjectExplorer's node.
        void checkCurrentNode ();

        // Project and document events handling.
        //! Handle change of Session's startup project.
        void handleStartupProjectChange (ProjectExplorer::Project *project);
        //! Check changed documents if it belongs to active project and not modified.
        void handleDocumentsChange (const QModelIndex &topLeft, const QModelIndex &bottomRight,
                                    const QVector<int> &roles);
        //! Check closing documents if it belongs to active project and was modified.
        void handleDocumentsClose (const QModelIndex &parent, int start, int end);
        //! Check built project if it is active and plugin got corresponding settings.
        void handleBuildStateChange (ProjectExplorer::Project *project);
        //! Handle project's fileListChanged signal.
        void handleProjectFileListChanged ();
        //! Handle session unload event.
        void handleSessionUnload ();

        // Task handling.
        //! Add task to ProjectExplorer's task lits.
        void addTask (char type, const QString &description,
                      const QString &fileName, int line);
        //! Clear self tasks for given files. All tasks if list is empty.
        void clearTasksForFiles (const QStringList& fileList = QStringList ());

        //! Apply updated settings data.
        void updateSettings ();

      private:
        void initMenus ();
        void initConnections ();
        void initLanguage ();

        //! Get checkable files for given node.
        QStringList checkableFiles (const ProjectExplorer::Node* node, bool forceSelected = false) const;

        //! Check given ProjectExplorer::Node.
        void checkNode (const ProjectExplorer::Node* node);
        //! Check given files. Terminate current check if forced is true.
        void checkFiles (const QStringList& fileNames);
        //! Check active project's open documents within given range with given modified flag.
        void checkActiveProjectDocuments (int beginRow, int endRow, bool modifiedFlag);

      private:
        //! Project's file names (keys) and their task infos (values).
        QHash<QString, TaskInfo> fileTasks_;
        //! Settings.
        Settings* settings_;
        //! Binary runner.
        CppcheckRunner* runner_;
        //! Checkable files list of active project.
        QStringList projectFileList_;
        //! Pointer to active project.
        QPointer<ProjectExplorer::Project> activeProject_;
    };

  } // namespace Internal
} // namespace QtcCppcheck

#endif // QTCCPPCHECK_H

