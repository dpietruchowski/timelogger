import QtQuick 2.9
import QtQuick.Controls 2.2

import "pages"

ApplicationWindow {
    id: window
    visible: true
    minimumWidth: 640
    minimumHeight: 480
    width: 640
    height: 480
    title: qsTr("Tabs")

    header: ToolBar {
        ToolButton {
            id: toolButton
            text: "\u2630"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: {
                drawer.open()
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
                model: ["Main Page", "Day logs"]
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
    }
}
