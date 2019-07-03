#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "TimeLogger.h"
#include "Timelog.h"
#include "Timespan.h"
#include "DayLogs.h"
#include "TimelogsModel.h"
#include "TimespansModel.h"

#include "TaskManager.h"
#include "TasksModel.h"
#include "TasksData.h"
#include "Tasks.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    const char* url = "Timelogger";

    QApplication app(argc, argv);

    TimeLogger timeLogger;
    timeLogger.initDatabase();
    timeLogger.updateDayLogs();

    TaskManager* taskManager = &TaskManager::Get();

    qRegisterMetaType<Timespan::Status>("TimespanStatus");
    qRegisterMetaType<Timelog::Type>("TimelogType");
    qRegisterMetaType<Task::Priority>("TaskPriority");
    qRegisterMetaType<Task::Status>("TaskStatus");

    qRegisterMetaType<TimelogsData*>("TimelogsData*");
    qRegisterMetaType<TimespansData*>("TimespansData*");
    qRegisterMetaType<TasksData*>("TasksData*");

    qmlRegisterType<TimeLogger>(url, 1, 0, "Timelogger");
    qmlRegisterUncreatableType<TaskManager>(url, 1, 0, "TaskManager", "Singleton");

    qmlRegisterType<DayLogs>(url, 1, 0, "DayLogs");
    qmlRegisterType<Tasks>(url, 1, 0, "Tasks");

    qmlRegisterType<TimelogsModel>(url, 1, 0, "TimelogsModel");
    qmlRegisterType<TimespansModel>(url, 1, 0, "TimespansModel");
    qmlRegisterType<TasksModel>(url, 1, 0, "TasksModel");

    qmlRegisterUncreatableType<Timespan>(url, 1, 0, "Timespan", "Not creatable as it is an enum type");
    qmlRegisterUncreatableType<Timelog>(url, 1, 0, "Timelog", "Not creatable as it is an enum type");
    qmlRegisterUncreatableType<Task>(url, 1, 0, "Task", "Not creatable as it is an enum type");

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("timeLogger", &timeLogger);
    engine.rootContext()->setContextProperty("taskManager", taskManager);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
