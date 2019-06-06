import QtQuick 2.0
import QtCharts 2.0
import QtQuick.Layouts 1.3

import Timelogger 1.0

Row {
    id: row
    spacing: 1
    Repeater {
        id: rep
        model: TimelogsModel {
            timelogs: timeLogger.daylogs.timelogs
        }
        delegate: Rectangle {
            width: row.width * (timespan.span / timeLogger.daylogs.sumspan)
            height: 10
            color: timespan.status === 0 ? "black" : (timespan.status === 1 ? "red" : "grey")
        }
    }
}
