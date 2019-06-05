
import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import Timelogger 1.0

import "../controls"

Page {
    width: 600
    height: 400

    header: Label {
        text: qsTr("Worklogger")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }


    ColumnLayout {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        InfoGrid {
            id: infoGrid
            Layout.alignment: Qt.AlignCenter
        }

        RowLayout {
            Layout.alignment: Qt.AlignCenter
            LogButton {
                id: startButton
                type:"Work"
                text: "Start"
            }

            LogButton {
                id: stopButton
                type: "Break"
                text: "Stop"
            }
        }
    }
}
