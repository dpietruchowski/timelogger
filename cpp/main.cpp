#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "TimeLogger.h"
#include "Timelog.h"
#include "Timespan.h"
#include "DayLogs.h"
#include "TimelogsModel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    TimeLogger timeLogger;
    timeLogger.initDatabase();
    timeLogger.updateDayLogs();

    qmlRegisterType<TimeLogger>("Classes", 1, 0, "Timelogger");
    qmlRegisterType<DayLogs>("Classes", 1, 0, "DayLogs");
    qmlRegisterType<TimelogsModel>("Classes", 1, 0, "TimelogsModel");
    qRegisterMetaType<Timespan>();
    qRegisterMetaType<Timelog>();

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("timeLogger", &timeLogger);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
