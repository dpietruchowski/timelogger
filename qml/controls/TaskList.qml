import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import Timelogger 1.0

Frame {
    signal taskClickedToView(variant task)
    property int taskStatus
    Tasks {
        id: tasks
        status: taskStatus
    }

    ListView {
        implicitWidth: 200
        implicitHeight: 380
        anchors.fill: parent
        clip: true
        focus: true

        model: TasksModel {
            tasks: tasks.tasks
        }

        delegate: RowLayout {
            width: parent.width
            ItemDelegate {
                implicitWidth: 35
                Label {
                    text: "<"
                    width: parent.width
                    height: parent.height
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: Qt.application.font.pixelSize * 1.5
                }
                enabled: taskStatus > Task.NotStarted
                onClicked: taskManager.changeTaskStatus(model.item.id, taskStatus - 1)
            }

            ItemDelegate {
                Layout.fillWidth: true
                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 10

                    Label {
                        text: model.item.id
                    }
                    Label {
                        text: model.item.title
                        Layout.fillWidth: true
                        elide: Text.ElideRight
                    }
                }
                onClicked: taskClickedToView(model.item)
            }

            ItemDelegate {
                implicitWidth: 35
                Label {
                    text: ">"
                    width: parent.width
                    height: parent.height
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: Qt.application.font.pixelSize * 1.5
                }
                enabled: taskStatus < Task.Done
                onClicked: taskManager.changeTaskStatus(model.item.id, (taskStatus + 1))
            }
        }
    }
}
