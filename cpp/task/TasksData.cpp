#include "TasksData.h"
#include <iterator>

void TasksData::add(const Task& newTask)
{
    if (contains(newTask.id))
        return;
    push_back(newTask);
}

void TasksData::remove(int id)
{
    if (auto iter = contains(id)) {
        erase(*iter);
    }
}

void TasksData::modify(const Task& modifiedTask)
{
    Tasks::Iterator iter = findTask(modifiedTask.id);
    set(iter, modifiedTask);
}

Task* TasksData::task(int id)
{
    auto result = findTask(id);
    if (result != end())
        return &(*result);
    else
        return nullptr;
}

const Task* TasksData::task(int id) const
{
    auto result = findTask(id);
    if (result != end())
        return &(*result);
    else
        return nullptr;
}

std::optional<TasksData::Tasks::Iterator> TasksData::contains(int id)
{
    auto result = findTask(id);
    if (result != end())
        return result;
    else
        return std::nullopt;
}

TasksData::Tasks::Iterator TasksData::findTask(int id)
{
    auto IdPredicate = [id] (const Task& log) {
        return log.id == id;
    };

    auto result = std::find_if(begin(), end(), IdPredicate);
    return result;
}

TasksData::ConstIterator TasksData::findTask(int id) const
{
    auto IdPredicate = [id] (const Task& log) {
        return log.id == id;
    };

    auto result = std::find_if(begin(), end(), IdPredicate);
    return result;
}
