#include "TasksModel.h"

TasksModel::TasksModel(QObject* parent)
    : VectorModel(parent)
{

}

TasksData* TasksModel::tasks() const
{
    return tasks_;
}

void TasksModel::setTasks(TasksData* tasks)
{
    tasks_ = tasks;
    setVector(tasks_);
}
