import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Item {
    width: 200; height: 50

    ColumnLayout {
        Row {
            spacing: 10
            Label { text: "Status:" }
            Label { text: timeLogger.status }
        }
        Row {
            spacing: 10
            Label { text: "Start time:" }
            Label { text: timeLogger.startTime }
        }
        Row {
            spacing: 10
            Label { text: "Last log:" }
            Label { text: timeLogger.lastLog }
        }
        Row {
            spacing: 10
            Label { text: "Sum of work" }
            Label { text: timeLogger.workspan }
        }
        Row {
            spacing: 10
            Label { text: "Sum of break" }
            Label { text: timeLogger.breakspan }
        }
    }
}
