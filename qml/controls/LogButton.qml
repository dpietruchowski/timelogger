import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import Timelogger 1.0

RoundButton {
    property string type

    Layout.alignment: Qt.AlignCenter
    enabled: timeLogger.status !== type

    font.pixelSize: Qt.application.font.pixelSize * 1.7
    onClicked: {
        if (type === "Work")
            timeLogger.logNow(Timelog.Start)
        if (type === "Break")
            timeLogger.logNow(Timelog.Stop)
    }
}
