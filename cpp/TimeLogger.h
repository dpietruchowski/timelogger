#ifndef TIMELOGGER_H
#define TIMELOGGER_H

#include <QObject>

#include "Timelog.h"
#include "DayLogs.h"

class TimeLogger : public QObject
{
    Q_OBJECT
    Q_PROPERTY(DayLogs* daylogs READ daylogs)
    Q_PROPERTY(QString status READ status NOTIFY todayLogsChanged)
    Q_PROPERTY(QString startTime READ startTime NOTIFY todayLogsChanged)
    Q_PROPERTY(QString lastLog READ lastLog NOTIFY todayLogsChanged)
    Q_PROPERTY(QString workspan READ workspan NOTIFY todayLogsChanged)
    Q_PROPERTY(QString breakspan READ breakspan NOTIFY todayLogsChanged)
public:
    static constexpr const char* kTableName = "timelogs";

    TimeLogger();

    void initDatabase();
    void updateDayLogs();

    DayLogs* daylogs();

    QString status() const;
    QString startTime() const;
    QString lastLog() const;
    QString workspan() const;
    QString breakspan() const;

public slots:
    void logNow(int logType);
    void addLog(const QDateTime& datetime, int logType);
    void removeLog(int id);

signals:
    void todayLogsChanged();

    void logAdded(const Timelog& timelog);
    void logRemoved(int id);

private:
    DayLogs dayLogs_;
};

#endif // TIMELOGGER_H
