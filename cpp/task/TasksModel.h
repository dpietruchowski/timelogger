#ifndef TASKSMODEL_H
#define TASKSMODEL_H

#include "VectorModel.h"
#include "TasksData.h"

class TasksModel : public VectorModel<Task>
{
    Q_OBJECT
    Q_PROPERTY(TasksData* tasks READ tasks WRITE setTasks)
 public:
     explicit TasksModel(QObject *parent = nullptr);

     TasksData* tasks() const;
     void setTasks(TasksData* tasks);

 private:
     TasksData* tasks_ = nullptr;
};

#endif // TASKSMODEL_H
