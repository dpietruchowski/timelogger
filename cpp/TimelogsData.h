#ifndef TIMELOGS_H
#define TIMELOGS_H

#include "Timelog.h"
#include "VectorData.h"

class TimelogsData : public VectorData<Timelog>
{
    using Timelogs = VectorData<Timelog>;
public:
    TimelogsData() = default;

    void add(const Timelog& log);
    void remove(int id);
    Timelog* timelog(int id);
    std::optional<Timelogs::Iterator> contains(int id);
    int index(Timelogs::Iterator iter) const;

private:
    Timelogs::Iterator findTimelog(int id);
};

#endif // TIMELOGS_H
