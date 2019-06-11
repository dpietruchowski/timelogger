#include "TimelogsData.h"

#include <iterator>

void TimelogsData::add(const Timelog& log)
{
    if (contains(log.id))
        return;
    push_back(log);
}

void TimelogsData::remove(int id)
{
    if (auto iter = contains(id)) {
        erase(*iter);
    }
}

Timelog* TimelogsData::timelog(int id)
{
    auto result = findTimelog(id);
    if (result != end())
        return &(*result);
    else
        return nullptr;
}

std::optional<TimelogsData::Timelogs::Iterator> TimelogsData::contains(int id)
{
    auto result = findTimelog(id);
    if (result != end())
        return result;
    else
        return std::nullopt;
}

int TimelogsData::index(Timelogs::Iterator iter) const
{
    return static_cast<int>(iter - begin());
}

TimelogsData::Timelogs::Iterator TimelogsData::findTimelog(int id)
{

    auto IdPredicate = [id] (const Timelog& log) {
        return log.id == id;
    };

    auto result = std::find_if(begin(), end(), IdPredicate);
    return result;
}
