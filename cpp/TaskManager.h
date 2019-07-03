#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <QObject>

#include "Task.h"

class QSqlDatabase;

class TaskManager : public QObject
{
    Q_OBJECT
public:
    static constexpr const char* kTableName = "tasks";
    static void createTable(QSqlDatabase& db);
    static TaskManager& Get();

private:
    TaskManager();


public slots:
    int addTask(int id, const QString& title, const QString& link,
                Task::Priority priority);
    int addTask(const Task& task);
    void removeTask(int id);

    void changeTaskStatus(int id, Task::Status status);
    void changeTaskNotes(int id, const QString& notes);

    void changeTask(int id, const QString& title, const QString& link,
                    Task::Priority priority);
    void changeTask(const Task& task);

private:
    Task getTask(int id);

signals:
    void taskAdded(const Task& task);
    void taskRemoved(int id);
    void taskChanged(const Task& task);
};

#endif // TASKMANAGER_H
