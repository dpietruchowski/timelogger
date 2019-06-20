#ifndef TIMELOGGER_H
#define TIMELOGGER_H

#include <QObject>

#include "Timelog.h"
#include "DayLogs.h"

class TimeLogger : public QObject
{
    Q_OBJECT
    Q_PROPERTY(DayLogs* daylogs READ daylogs NOTIFY daylogsChanged)
    Q_PROPERTY(QString status READ status NOTIFY todayLogsChanged)
public:
    static constexpr const char* kTableName = "timelogs";

    TimeLogger();

    void initDatabase();
    void updateDayLogs();

    DayLogs* daylogs();

    QString status() const;

public slots:
    int logNow(Timelog::Type logType);
    int addLog(const QDateTime& datetime, Timelog::Type logType);
    void removeLog(int id);

signals:
    void todayLogsChanged();
    void daylogsChanged();

    void logAdded(const Timelog& timelog);
    void logRemoved(int id);

private:
    DayLogs dayLogs_;
};

#endif // TIMELOGGER_H
