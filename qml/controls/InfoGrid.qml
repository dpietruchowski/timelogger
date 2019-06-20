import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import Timelogger 1.0

Item {
    property DayLogs dayLogs
    property string status
    width: 200; height: 50

    ColumnLayout {
        Row {
            spacing: 10
            Label { text: "Status:" }
            Label { text: status }
        }
        Row {
            spacing: 10
            Label { text: "Start time:" }
            Label { text: dayLogs.startTime.time }
        }
        Row {
            spacing: 10
            Label { text: "Last log:" }
            Label { text: dayLogs.lastLog.time }
        }
        Row {
            spacing: 10
            Label { text: "Sum of work" }
            Label { text: dayLogs.workspan.spanStr }
        }
        Row {
            spacing: 10
            Label { text: "Sum of break" }
            Label { text: dayLogs.breakspan.spanStr }
        }
    }
}
