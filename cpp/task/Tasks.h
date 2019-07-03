#ifndef TASKS_H
#define TASKS_H

#include <QObject>
#include "TasksData.h"

class Tasks: public QObject
{
    Q_OBJECT
    Q_PROPERTY(TasksData* tasks READ getTasks CONSTANT)
    Q_PROPERTY(Task::Status status READ status WRITE setStatus)
public:
    Tasks();

    TasksData* getTasks();

    Task::Status status() const;
    void setStatus(Task::Status status);

private:
    void loadFromDatabase();

private:
    Task::Status status_;
    TasksData data_;
};

#endif // TASKS_H
