#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "TimeLogger.h"
#include "Timelog.h"
#include "Timespan.h"
#include "DayLogs.h"
#include "TimelogsModel.h"
#include "TimespansModel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    TimeLogger timeLogger;
    timeLogger.initDatabase();
    timeLogger.updateDayLogs();

    qRegisterMetaType<Timespan::Status>("TimespanStatus");
    qRegisterMetaType<Timelog::Type>("TimelogType");
    qRegisterMetaType<TimelogsData*>("TimelogsData*");
    qRegisterMetaType<TimespansData*>("TimespansData*");

    qmlRegisterType<TimeLogger>("Timelogger", 1, 0, "Timelogger");
    qmlRegisterType<DayLogs>("Timelogger", 1, 0, "DayLogs");
    qmlRegisterType<TimelogsModel>("Timelogger", 1, 0, "TimelogsModel");
    qmlRegisterType<TimespansModel>("Timelogger", 1, 0, "TimespansModel");

    qmlRegisterUncreatableType<Timespan>("Timelogger", 1, 0, "Timespan", "Not creatable as it is an enum type");
    qmlRegisterUncreatableType<Timelog>("Timelogger", 1, 0, "Timelog", "Not creatable as it is an enum type");

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("timeLogger", &timeLogger);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
