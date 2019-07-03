#ifndef TASK_H
#define TASK_H

#include <QObject>

struct Task
{
    Q_GADGET
    Q_PROPERTY(int id MEMBER id)
    Q_PROPERTY(QString title MEMBER title)
    Q_PROPERTY(QString link MEMBER link)
    Q_PROPERTY(Priority priority MEMBER priority)
    Q_PROPERTY(Status status MEMBER status)
    Q_PROPERTY(QString notes MEMBER notes)

    Q_PROPERTY(QString statusStr READ statusStr CONSTANT)
    Q_PROPERTY(QString priorityStr READ priorityStr CONSTANT)

public:
    enum Priority {
        High,
        Medium,
        Low
    };
    Q_ENUM(Priority)

    enum Status {
        NotStarted,
        InProgress,
        UnderReview,
        Done
    };
    Q_ENUM(Status)

    QString statusStr() const;
    QString priorityStr() const;
    static Status statusFromStr(const QString& status);
    static QString statusToStr(Status status);
    static Priority priorityFromStr(const QString& status);
    static QString priorityToStr(Priority priority);

    int id = -1;
    QString title;
    QString link;
    Priority priority = Low;
    Status status = NotStarted;
    QString notes;
};

#endif // TASK_H
