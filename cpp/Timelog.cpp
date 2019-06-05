#include "Timelog.h"

Timelog::Type Timelog::otherType(Timelog::Type type)
{
    return type == Timelog::Start ? Timelog::Stop : Timelog::Start;
}

Timespan Timelog::timespan(const Timelog& next) const
{
    Timespan span;
    span.span = timestamp.msecsTo(next.timestamp);
    if (span.span != 0) {
        if (type == Timelog::Start && next.type == Timelog::Stop) {
            span.status = Timespan::Work;
        } else if (type == Timelog::Stop && next.type == Timelog::Start) {
            span.status = Timespan::Break;
        } else {
            span.status = Timespan::Undefined;
        }
    }
    return span;
}
