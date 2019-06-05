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

class TimeLogger;

class DayLogs: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QDate date READ date WRITE setDate)
    Q_PROPERTY(TimeLogger* timelogger READ getTimeLogger WRITE setTimeLogger)
    Q_PROPERTY(TimelogsData* timelogs READ getTimelogs)

public:
    DayLogs(): QObject(nullptr) {}
    ~DayLogs() override {}

    void loadFromDatabase();

    QDate date() { return date_; }
    void setDate(const QDate& date);

    TimeLogger* getTimeLogger() const;
    void setTimeLogger(TimeLogger* timelogger);

    TimelogsData* getTimelogs();

    const TimelogsData& timelogs() const;

    qint64 workspan() const;
    qint64 breakspan() const;

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
    qint64 breakspan_ = 0;
    qint64 workspan_ = 0;
    qint64 undefinedspan_ = 0;
};

#endif // DAYLOGS_H
