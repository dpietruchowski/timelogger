#include "Timespan.h"

#include <QTime>

QString Timespan::spanStr() const
{
    QTime time(0, 0, 0, 0);
    time = time.addMSecs(span);
    return time.toString() + QString("(%1)").arg(span);
}

QString Timespan::statusStr() const
{
    switch(status) {
        case Status::Work: return "Work";
        case Status::Break: return "Break";
        case Status::Undefined: return "Undefined";
    }
    return "Error";
}
