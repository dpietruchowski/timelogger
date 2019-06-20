#ifndef DAYLOGS_H
#define DAYLOGS_H

#include <QObject>
#include <QDate>
#include <QTime>
#include <QVariantList>

#include <optional>
#include <vector>

#include "Timelog.h"
#include "Timespan.h"
#include "TimelogsData.h"
#include "TimespansData.h"

class TimeLogger;

class DayLogs: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QDate date READ date WRITE setDate)
    Q_PROPERTY(TimeLogger* timelogger READ getTimeLogger WRITE setTimeLogger)
    Q_PROPERTY(TimelogsData* timelogs READ getTimelogs)
    Q_PROPERTY(TimespansData* timespans READ getTimespans)
    Q_PROPERTY(Timespan workspan READ workspan NOTIFY changed)
    Q_PROPERTY(Timespan breakspan READ breakspan NOTIFY changed)
    Q_PROPERTY(Timespan sumspan READ sumspan NOTIFY changed)
    Q_PROPERTY(Timelog startTime READ startTime NOTIFY changed)
    Q_PROPERTY(Timelog lastLog READ lastLog NOTIFY changed)

public:
    DayLogs();
    ~DayLogs() override {}

    void loadFromDatabase();

    QDate date() { return date_; }
    void setDate(const QDate& date);

    TimeLogger* getTimeLogger() const;
    void setTimeLogger(TimeLogger* timelogger);

    TimelogsData* getTimelogs();
    TimespansData* getTimespans();

    const TimelogsData& timelogs() const;

    Timespan workspan() const;
    Timespan breakspan() const;
    Timespan sumspan() const;
    Timelog startTime() const;
    Timelog lastLog() const;

signals:
    void preDateSet();
    void postDateSet();
    void changed();

private:
    void update();
    void countSpans();

private:
    TimeLogger* timeLogger_ = nullptr;
    QDate date_;
    TimelogsData timelogs_;
    TimespansData timespans_;
    qint64 breakspan_ = 0;
    qint64 workspan_ = 0;
    qint64 undefinedspan_ = 0;
};

#endif // DAYLOGS_H
