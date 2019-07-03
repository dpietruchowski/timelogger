#ifndef TASKSDATA_H
#define TASKSDATA_H

#include "Task.h"
#include "VectorData.h"

class TasksData : public VectorData<Task>
{
    using Tasks = VectorData<Task>;
public:
    TasksData() = default;

    void add(const Task& newTask);
    void remove(int id);
    void modify(const Task& modifiedTask);
    Task* task(int id);
    const Task* task(int id) const;
    std::optional<Tasks::Iterator> contains(int id);

private:
    Tasks::Iterator findTask(int id);
    Tasks::ConstIterator findTask(int id) const;
};

#endif // TASKSDATA_H
