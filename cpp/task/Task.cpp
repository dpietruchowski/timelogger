#include "Task.h"

QString Task::statusStr() const
{
    return statusToStr(status);
}

QString Task::priorityStr() const
{
    return priorityToStr(priority);
}

Task::Status Task::statusFromStr(const QString& status)
{
    if (status == "Not started") return Status::NotStarted;
    if (status == "In progress") return Status::InProgress;
    if (status == "Under review") return Status::UnderReview;
    if (status == "Done") return Status::Done;
    return Status::NotStarted;
}

QString Task::statusToStr(Task::Status status)
{
    switch(status) {
        case Status::NotStarted: return "Not started";
        case Status::InProgress: return "In progress";
        case Status::UnderReview: return "Under review";
        case Status::Done: return "Done";
        default: return "";
    }
}

Task::Priority Task::priorityFromStr(const QString& status)
{
    if (status == "Low") return Priority::Low;
    if (status == "Medium") return Priority::Medium;
    if (status == "High") return Priority::High;
    return Priority::Low;
}

QString Task::priorityToStr(Task::Priority priority)
{
    switch(priority) {
        case Priority::Low: return "Low";
        case Priority::Medium: return "Medium";
        case Priority::High: return "High";
        default: return "";
    }
}
