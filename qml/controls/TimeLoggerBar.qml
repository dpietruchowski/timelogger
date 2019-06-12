import QtQuick 2.0
import QtCharts 2.0
import QtQuick.Layouts 1.3

import Timelogger 1.0

Row {
    id: row
    spacing: 1
    Repeater {
        id: rep
        model: TimespansModel {
            timespans: timeLogger.daylogs.timespans
        }
        delegate: Rectangle {
            width: row.width * (item.span / timeLogger.daylogs.sumspan)
            height: 10
            color: item.status === Timespan.Work ? "black" : (item.status === Timespan.Break ? "red" : "grey")
        }
    }
}
