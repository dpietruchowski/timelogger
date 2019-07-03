#include "Tasks.h"

#include <QtSql>

#include "TaskManager.h"

Tasks::Tasks(): QObject ()
{
    TaskManager* manager = &TaskManager::Get();
    connect(manager, &TaskManager::taskAdded,
            [this] (const Task& task) {
        if (task.status == status_)
            data_.add(task);
    });
    connect(manager, &TaskManager::taskRemoved,
            [this] (int id) {
        if (data_.contains(id))
            data_.remove(id);
    });

    auto OnTaskChange = [this] (const Task& task) {
        bool contains = data_.contains(task.id) != std::nullopt;
        bool statusMatch = task.status == status_;
        if (contains && statusMatch)
            data_.modify(task);
        else if (contains && !statusMatch)
            data_.remove(task.id);
        else if (!contains && statusMatch)
            data_.add(task);
    };
    connect(manager, &TaskManager::taskChanged, OnTaskChange);
    loadFromDatabase();
}

TasksData* Tasks::getTasks()
{
    return &data_;
}

Task::Status Tasks::status() const
{
    return status_;
}

void Tasks::setStatus(Task::Status _status)
{
    status_ = _status;
    loadFromDatabase();
}

void Tasks::loadFromDatabase()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM tasks"
                  " WHERE status = ?"
                  " ORDER BY priority ASC");
    query.addBindValue(Task::statusToStr(status_));
    query.exec();
    QSqlQueryModel model;
    model.setQuery(query);

    data_.clear();
    for (int i = 0; i < model.rowCount(); ++i) {
        Task task;
        task.id = model.record(i).value("id").toInt();
        task.title = model.record(i).value("title").toString();
        task.link = model.record(i).value("link").toString();
        task.priority = Task::priorityFromStr(model.record(i).value("priority").toString());
        task.status = Task::statusFromStr(model.record(i).value("status").toString());
        task.notes = Task::statusFromStr(model.record(i).value("status").toString());
        data_.add(task);
    }
}
