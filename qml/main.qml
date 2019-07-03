import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import "pages"

ApplicationWindow {
    id: window
    visible: true
    minimumWidth: 1000
    minimumHeight: 480
    width: 1000
    height: 480
    title: qsTr("Tabs")

    header: ToolBar {
        RowLayout {
            anchors.fill: parent
            ToolButton {
                Layout.alignment: Qt.AlignLeft
                id: toolButton
                text: "\u2630"
                font.pixelSize: Qt.application.font.pixelSize * 1.6
                onClicked: {
                    drawer.open()
                }
            }
            Text {
                Layout.alignment: Qt.AlignCenter
                text: Qt.formatDateTime(new Date(), "dd MMM yyyy")
                font.pixelSize: Qt.application.font.pixelSize * 1.6
            }
        }
    }

    Drawer {
        id: drawer
        width: 0.66 * window.width
        height: window.height

        Column {
            anchors.fill: parent

            Repeater {
                model: ["Main Page", "Day logs", "Tasks"]
                ItemDelegate {
                    text: qsTr(modelData)
                    width: parent.width
                    onClicked: {
                        swipeView.currentIndex = index
                        drawer.close()
                    }
                }
            }
        }
    }

    SwipeView {
        id: swipeView
        anchors.fill: parent

        MainPage {
        }
        DayLogsPage {
        }
        TasksPage {
        }
    }
}
