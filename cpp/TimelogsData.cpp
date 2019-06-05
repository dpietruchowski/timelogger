#include "TimelogsData.h"

#include <iterator>

TimelogsData::Timelogs::const_iterator TimelogsData::begin() const
{
    return std::begin(timelogs_);
}

TimelogsData::Timelogs::const_iterator TimelogsData::end() const
{
    return std::end(timelogs_);
}

int TimelogsData::size() const
{
    return static_cast<int>(timelogs_.size());
}

void TimelogsData::clear()
{
    timelogs_.clear();
}

const Timelog& TimelogsData::operator[](int idx) const
{
    return timelogs_[static_cast<size_t>(idx)];
}

const Timelog& TimelogsData::front() const
{
    return timelogs_.front();
}

const Timelog& TimelogsData::back() const
{
    return timelogs_.back();
}

void TimelogsData::add(const Timelog& log)
{
    if (contains(log.id))
        return;
    emit preLogAdded(size());
    timelogs_.push_back(log);
    emit postLogAdded();
}

void TimelogsData::remove(int id)
{
    if (auto iter = contains(id)) {
        emit preLogRemoved(index(*iter));
        timelogs_.erase(*iter);
        emit postLogRemoved();
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

std::optional<TimelogsData::Timelogs::iterator> TimelogsData::contains(int id)
{
    auto result = findTimelog(id);
    if (result != end())
        return result;
    else
        return std::nullopt;
}

int TimelogsData::index(Timelogs::iterator iter) const
{
    return static_cast<int>(iter - begin());
}

TimelogsData::Timelogs::iterator TimelogsData::begin()
{
    return timelogs_.begin();
}

TimelogsData::Timelogs::iterator TimelogsData::end()
{
    return timelogs_.end();
}

TimelogsData::Timelogs::iterator TimelogsData::findTimelog(int id)
{

    auto IdPredicate = [id] (const Timelog& log) {
        return log.id == id;
    };

    auto result = std::find_if(begin(), end(), IdPredicate);
    return result;
}
