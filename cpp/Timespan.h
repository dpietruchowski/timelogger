#ifndef TIMESPAN_H
#define TIMESPAN_H

#include <QObject>

struct Timespan {
    Q_GADGET
    Q_PROPERTY(qint64 span MEMBER span)
    Q_PROPERTY(Status status MEMBER status)
public:
    enum Status {
        Work,
        Break,
        Undefined
    };
    Q_ENUM(Status)

    qint64 span;
    Status status;
};

Q_DECLARE_METATYPE(Timespan)

#endif // TIMESPAN_H
