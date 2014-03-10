#ifndef TASKINFO_H
#define TASKINFO_H

#include <QString>

namespace ProjectExplorer
{
  class Task;
}

namespace QtcCppcheck {
  namespace Internal {

    /*!
 * \brief Task information holder.
 * Required to prevend addition of duplicate tasks in situations where
 * tasks found for non-checking files (checking cpp -> reported for header).
 */
    class TaskInfo
    {
      public:
        TaskInfo();
        TaskInfo(uint line, const QString& description);
        TaskInfo (const ProjectExplorer::Task& source);

        void init (ProjectExplorer::Task& task) const;
        TaskInfo& operator=(const ProjectExplorer::Task& right);
        bool operator==(const TaskInfo& right) const;

      private:
        uint id_;
        QString description_;
        int line_;
    };

  } // namespace Internal
} // namespace QtcCppcheck

#endif // TASKINFO_H
