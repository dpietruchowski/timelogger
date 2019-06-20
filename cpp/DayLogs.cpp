#include "DayLogs.h"

#include <QtSql>
#include <QVariantList>

#include "TimeLogger.h"

DayLogs::DayLogs(): QObject(nullptr)
{
    auto MapIdxTimelogToTimespan = [this] (int idx) {
        if (timelogs_.size() < 2)
            return -1;

        int lastIdx = timelogs_.size() - 1;
        int retIdx = -1;
        if (0 <= idx && idx < lastIdx) {
            retIdx = idx;
        } else if (idx == lastIdx) {
            retIdx = idx - 1;
        } else {
            qWarning("Timelogs idx out of range: idx (%d) where size (%d)", idx, timelogs_.size());
        }
        return retIdx;
    };
    connect(&timelogs_, &TimelogsData::postItemAdded,
            [this, MapIdxTimelogToTimespan] (int idx) {
        int lastIdx = timelogs_.size() - 1;
        int insertedIdx = MapIdxTimelogToTimespan(idx);
        if (insertedIdx == -1) return;

        Timespan timespan = timelogs_[insertedIdx].timespan(timelogs_[insertedIdx+1]);
        timespans_.insert(insertedIdx, timespan);

        if (0 < idx && idx < lastIdx) {
            int prevIdx = insertedIdx - 1;
            timespans_.set(prevIdx, timelogs_[prevIdx].timespan(timelogs_[prevIdx+1]));
        }
        update();
    });
    connect(&timelogs_, &TimelogsData::postItemRemoved,
            [this,  MapIdxTimelogToTimespan] (int idx) {
        int lastIdx = timelogs_.size() - 1;
        int removedIdx = MapIdxTimelogToTimespan(idx);
        if (removedIdx == -1) {
            timespans_.clear();
            return;
        }

        timespans_.erase(removedIdx);

        if (0 < idx && idx < lastIdx) {
            int prevIdx = removedIdx - 1;
            timespans_.set(prevIdx, timelogs_[prevIdx].timespan(timelogs_[prevIdx+1]));
        }
        update();
    });
}

void DayLogs::loadFromDatabase()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM timelogs"
                  " WHERE date(timestamp) = date(?)"
                  " ORDER BY timestamp ASC");
    //query.addBindValue(Timelogger::kTableName);
    query.addBindValue(date_);
    query.exec();
    QSqlQueryModel model;
    model.setQuery(query);

    timelogs_.clear();
    for (int i = 0; i < model.rowCount(); ++i) {
        QDateTime timestamp = model.record(i).value("timestamp").toDateTime();
        Timelog::Type type = model.record(i).value("type").toString() == "Start" ?
                    Timelog::Start : Timelog::Stop;
        int id = model.record(i).value("id").toInt();
        timelogs_.add({id, timestamp, type});
    }
    update();
}

void DayLogs::setDate(const QDate& date)
{
    emit preDateSet();
    date_ = date;
    loadFromDatabase();
    emit postDateSet();
}

TimeLogger* DayLogs::getTimeLogger() const
{
    return timeLogger_;
}

void DayLogs::setTimeLogger(TimeLogger* timelogger)
{
    timeLogger_ = timelogger;
    connect(timelogger, &TimeLogger::logAdded, &timelogs_, &TimelogsData::add);
    connect(timelogger, &TimeLogger::logRemoved, &timelogs_, &TimelogsData::remove);
}

TimelogsData* DayLogs::getTimelogs()
{
    return &timelogs_;
}

TimespansData* DayLogs::getTimespans()
{
    return &timespans_;
}

const TimelogsData& DayLogs::timelogs() const
{
    return timelogs_;
}

Timespan DayLogs::workspan() const
{
    return {workspan_, Timespan::Work};
}

Timespan DayLogs::breakspan() const
{
    return {breakspan_, Timespan::Break};
}

Timespan DayLogs::sumspan() const
{
    return {workspan_ + breakspan_ + undefinedspan_, Timespan::Undefined};
}

Timelog DayLogs::startTime() const
{
    if (timelogs_.size() > 0)
        return timelogs_.front();
    return Timelog();
}

Timelog DayLogs::lastLog() const
{
    if (timelogs_.size() > 0)
        return timelogs_.back();
    return Timelog();
}

void DayLogs::update()
{
    countSpans();
    emit changed();
}

void DayLogs::countSpans()
{
    breakspan_ = workspan_ = undefinedspan_ = 0;

    for (const auto& timespan: timespans_) {
        if (timespan.status == Timespan::Work)
            workspan_ += timespan.span;
        else if (timespan.status == Timespan::Break)
            breakspan_ += timespan.span;
        else
            undefinedspan_ += timespan.span;
    }
}

