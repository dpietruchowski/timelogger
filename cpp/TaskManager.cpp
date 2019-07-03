#include "TaskManager.h"

#include <QDebug>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

TaskManager::TaskManager()
{

}

int TaskManager::addTask(int id, const QString& title, const QString& link,
                         Task::Priority priority)
{
    return addTask(Task{id, title, link, priority, Task::NotStarted, ""});
}

void TaskManager::createTable(QSqlDatabase& db)
{
    if(!db.tables().contains("tasks")) {
        QSqlQuery query;
        bool result = query.exec("CREATE TABLE tasks "
                   "(id integer primary key, "
                   "title varchar(40),"
                   "link varchar(100),"
                   "priority varchar(10),"
                   "status varchar(10),"
                   "notes text)");
        if (!result) {
            qDebug() << query.lastError().text();
        }
    }
}

TaskManager& TaskManager::Get()
{
    static TaskManager manager;
    return manager;
}

int TaskManager::addTask(const Task& task)
{
    QSqlQuery query;
    query.prepare(QString("insert into ") + TaskManager::kTableName + " (id, title, link, priority, status, notes) values (?, ?, ?, ?, ?, ?)");
    query.addBindValue(task.id);
    query.addBindValue(task.title);
    query.addBindValue(task.link);
    query.addBindValue(task.priorityStr());
    query.addBindValue(task.statusStr());
    query.addBindValue(task.notes);
    if (!query.exec()) {
        qDebug() << query.lastError().text();
        return -1;
    }
    emit taskAdded(task);
    return task.id;
}

void TaskManager::removeTask(int id)
{
    QSqlQuery query;
    query.prepare(QString("delete from ") + TaskManager::kTableName + " where id = ?");
    query.addBindValue(id);
    if (!query.exec()) {
        qDebug() << query.lastError().text();
        return;
    }
    emit taskRemoved(id);
}

void TaskManager::changeTaskStatus(int id, Task::Status status)
{
    QSqlQuery query;
    query.prepare(QString("update ") + TaskManager::kTableName + " set status = ? where id = ?");

    query.addBindValue(Task::statusToStr(status));
    query.addBindValue(id);
    if (!query.exec()) {
        qDebug() << query.boundValues();
        qDebug() << query.lastError().text();
        return;
    }
    emit taskChanged(getTask(id));
}

void TaskManager::changeTaskNotes(int id, const QString& notes)
{
    Task task = getTask(id);
    task.notes = notes;
    changeTask(task);
}

void TaskManager::changeTask(int id, const QString& title, const QString& link,
                             Task::Priority priority)
{
    Task task = getTask(id);
    task.title = title;
    task.link = link;
    task.priority = priority;
    changeTask(task);
}

void TaskManager::changeTask(const Task& task)
{
    QSqlQuery query;
    query.prepare(QString("update ") + TaskManager::kTableName + " set title = ?, link = ?, priority = ?, status = ?, notes = ? where id = ?");

    query.addBindValue(task.title);
    query.addBindValue(task.link);
    query.addBindValue(task.priorityStr());
    query.addBindValue(task.statusStr());
    query.addBindValue(task.notes);
    query.addBindValue(task.id);

    if (!query.exec()) {
        qDebug() << query.lastError().text();
        return;
    }
    emit taskChanged(task);
}

Task TaskManager::getTask(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM tasks"
                  " WHERE id = ?");
    query.addBindValue(id);
    if (!query.exec()) {
        qDebug() << query.lastError().text();
        return {};
    }

    Task task;
    if (query.next())
    {
        task.id = query.value("id").toInt();
        task.title = query.value("title").toString();
        task.link = query.value("link").toString();
        task.priority = Task::priorityFromStr(query.value("priority").toString());
        task.status = Task::statusFromStr(query.value("status").toString());
        task.notes = Task::statusFromStr(query.value("status").toString());
    }
    return task;
}
