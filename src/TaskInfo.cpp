#include <projectexplorer/task.h>

#include "TaskInfo.h"
#include "Constants.h"

using namespace QtcCppcheck::Internal;

TaskInfo::TaskInfo() :
  id_ (-1), line_ (-1)
{
}

TaskInfo::TaskInfo(uint line, const QString &description) :
  id_ (-1), description_ (description), line_ (line)
{

}

TaskInfo::TaskInfo (const ProjectExplorer::Task& source) :
  id_ (-1), line_ (-1)
{
  *this = source;
}

void TaskInfo::init(ProjectExplorer::Task &task) const
{
  // Set only required fields.
  task.taskId = id_;
  task.category = Constants::TASK_CATEGORY_ID;
}

TaskInfo &TaskInfo::operator=(const ProjectExplorer::Task &right)
{
  id_ = right.taskId;
  description_ = right.description;
  line_ = right.line;
  return (*this);
}


bool TaskInfo::operator==(const TaskInfo &right) const
{
  return (description_ == right.description_ &&
          line_ == right.line_);
}
