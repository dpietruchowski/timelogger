#include "DayLogs.h"

#include <QtSql>
#include <QVariantList>

#include "TimeLogger.h"

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
    connect(timelogger, &TimeLogger::logAdded, this, &DayLogs::update);
    connect(timelogger, &TimeLogger::logRemoved, this, &DayLogs::update);
}

TimelogsData* DayLogs::getTimelogs()
{
    return &timelogs_;
}

const TimelogsData& DayLogs::timelogs() const
{
    return timelogs_;
}

qint64 DayLogs::workspan() const
{
    return workspan_;
}

qint64 DayLogs::breakspan() const
{
    return breakspan_;
}

qint64 DayLogs::sumspan() const
{
    return workspan() + breakspan() + undefinedspan_;
}

void DayLogs::update()
{
    countSpans();
    changed();
}

void DayLogs::countSpans()
{
    breakspan_ = workspan_ = undefinedspan_ = 0;

    for(int i = 0; i < timelogs_.size() - 1; ++i) {
        Timespan timespan = timelogs_[i].timespan(timelogs_[i+1]);
        if (timespan.status == Timespan::Work)
            workspan_ += timespan.span;
        else if (timespan.status == Timespan::Break)
            breakspan_ += timespan.span;
        else
            undefinedspan_ += timespan.span;
    }
}

