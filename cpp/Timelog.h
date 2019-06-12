#ifndef TIMELOG_H
#define TIMELOG_H

#include <QObject>
#include <QDateTime>

#include "Timespan.h"

struct Timelog {
    Q_GADGET
    Q_PROPERTY(int id MEMBER id)
    Q_PROPERTY(QDateTime timestamp MEMBER timestamp)
    Q_PROPERTY(Type type MEMBER type)

    Q_PROPERTY(QString typeStr READ typeStr CONSTANT)
    Q_PROPERTY(QString date READ date CONSTANT)
    Q_PROPERTY(QString time READ time CONSTANT)
public:
    enum Type {
        Start,
        Stop
    };
    Q_ENUM(Type)

    static Type otherType(Type type);

    int id = -1;
    QDateTime timestamp;
    Type type = Type::Start;

    QString date() { return timestamp.date().toString(); }
    QString time() { return timestamp.time().toString(); }
    QString typeStr() { return type == Start ? "Start" : "Stop"; }

    Timespan timespan(const Timelog& next) const;
};

Q_DECLARE_METATYPE(Timelog)

#endif // TIMELOG_H
