import QtQuick 2.0
import QtQuick.Controls 1.5
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import Timelogger 1.0

Page {
    width: 600
    height: 400
    title: "All logs"

    DayLogs {
        id: daylogs
        date: calendar.selectedDate
        timelogger: timeLogger
    }

    RowLayout {
        anchors.fill: parent
        anchors.margins: 30
        spacing: 20
        Frame {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignCenter
            id: listFrame

            ListView {
                implicitWidth: 200
                implicitHeight: 380
                anchors.fill: parent
                clip: true
                focus: true

                model: TimelogsModel {
                    timelogs: daylogs.timelogs
                }

                delegate: RowLayout {
                    width: parent.width
                    ItemDelegate {
                        Layout.fillWidth: true
                        RowLayout {
                            width: parent.width
                            height: parent.height

                            Text {
                                Layout.preferredWidth: 50
                                text: model.timelog.id
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                            }
                            Text {
                                Layout.fillWidth: true
                                text: model.timelog.time
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                            }
                            Text {
                                Layout.preferredWidth: 50
                                text: model.timelog.typeStr
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                            }
                        }
                    }
                    ItemDelegate {
                        Layout.preferredWidth: 50

                        Text {
                            text: "X"
                            width: parent.width
                            height: parent.height
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            font.pixelSize: Qt.application.font.pixelSize * 1.5
                        }

                        onClicked: {
                            timeLogger.removeLog(model.timelog.id)
                        }
                    }
                }
            }
        }

        Calendar {
            Layout.alignment: Qt.AlignCenter
            Layout.fillWidth: true
            Layout.fillHeight: true
            id: calendar
        }
    }
}
