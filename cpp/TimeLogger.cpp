#include "TimeLogger.h"

#include <QDebug>
#include <QTimerEvent>

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
    if (dayLogs_.timespans().size() == 0)
        return "Break";
    return dayLogs_.timespans().back().status == Timespan::Work ? "Work" : "Break";
}

int TimeLogger::logNow(Timelog::Type logType)
{
    removeCurrentLog();
    int result = addLog(QDateTime::currentDateTime(), logType);
    addCurrentLog();
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
    emit todayLogsChanged();
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
    emit todayLogsChanged();
    if (id == currentLogId)
        currentLogId = -1;
}

void TimeLogger::onTimer()
{
    removeCurrentLog();
    addCurrentLog();
}

void TimeLogger::removeCurrentLog()
{
    if (currentLogId != -1) {
        emit logRemoved(currentLogId);
        emit todayLogsChanged();
        currentLogId = -1;
    }
}

void TimeLogger::addCurrentLog()
{
    Timelog::Type type = Timelog::Start;
    if (daylogs()->timelogs().size() > 0)
        type = Timelog::otherType(daylogs()->timelogs().back().type);

    Timelog log = {-2, QDateTime::currentDateTime(), type};
    currentLogId = log.id;
    emit logAdded(log);
    emit todayLogsChanged();
}
