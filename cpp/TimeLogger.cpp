#include "TimeLogger.h"

#include <QDebug>

#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

TimeLogger::TimeLogger()
{
}

void TimeLogger::initDatabase()
{
    QString path = "timelogger";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    db.open();
    if(!db.tables().contains("timelogs")) {
        QSqlQuery query;
        bool result = query.exec("CREATE TABLE timelogs "
                   "(id integer primary key autoincrement, "
                   "type varchar(5),"
                   "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP)");
        if (!result) {
            qDebug() << query.lastError().text();
        }
    }

}

void TimeLogger::updateDayLogs()
{
    dayLogs_.setDate(QDate::currentDate());
    dayLogs_.setTimeLogger(this);
}

DayLogs* TimeLogger::daylogs()
{
    return &dayLogs_;
}

QString TimeLogger::status() const
{
    if (dayLogs_.timelogs().size() == 0)
        return "Break";
    return dayLogs_.timelogs().back().type == Timelog::Start ? "Work" : "Break";
}

QString TimeLogger::startTime() const
{
    if (dayLogs_.timelogs().size() == 0)
        return "Not started yet";
    return dayLogs_.timelogs().front().timestamp.time().toString();
}

QString TimeLogger::lastLog() const
{
    if (dayLogs_.timelogs().size() == 0)
        return "Not started yet";
    QString format = "%1 %2";
    Timelog timelog = dayLogs_.timelogs().back();
    return format.arg(timelog.timestamp.time().toString()).arg(timelog.type == Timelog::Start ? "Start" : "Stop");
}

QString TimeLogger::workspan() const
{
    QTime time(0, 0, 0, 0);
    time = time.addMSecs(dayLogs_.workspan());
    return time.toString();
}

QString TimeLogger::breakspan() const
{
    QTime time(0, 0, 0, 0);
    time = time.addMSecs(dayLogs_.breakspan());
    return time.toString();
}

int TimeLogger::logNow(Timelog::Type logType)
{
    int result = addLog(QDateTime::currentDateTime(), logType);
    emit todayLogsChanged();
    return result;
}

int TimeLogger::addLog(const QDateTime& datetime, Timelog::Type logType)
{
    Timelog log = {-1, datetime, logType};
    QSqlQuery query;
    query.prepare(QString("insert into ") + TimeLogger::kTableName + " (type, timestamp) values (?, ?)");
    query.addBindValue(log.type == Timelog::Start ? "Start" : "Stop");
    query.addBindValue(log.timestamp);
    if (!query.exec()) {
        qDebug() << query.lastError().text();
        return -1;
    }
    log.id = query.lastInsertId().toInt();
    emit logAdded(log);
    return log.id;
}

void TimeLogger::removeLog(int id)
{
    QSqlQuery query;
    query.prepare(QString("delete from ") + TimeLogger::kTableName + " where id = ?");
    query.addBindValue(id);
    if (!query.exec()) {
        qDebug() << query.lastError().text();
        return;
    }
    emit logRemoved(id);
}
