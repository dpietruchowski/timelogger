import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import Timelogger 1.0

import "../controls"

Dialog {
    property int taskId
    property string taskTitle
    property int taskPriority
    property string taskLink

    function clearTaskValues() {
        taskId = 0;
        taskTitle = ""
        taskPriority = 0
        taskLink = ""
    }

    width: parent.width - 20
    height: parent.height - 20
    x: (parent.width - width) / 2
    y: (parent.height - height) / 2
    standardButtons: Dialog.Ok | Dialog.Cancel

    GridLayout {
        columns: 2
        anchors.fill: parent
        anchors.margins: 10
        rowSpacing: 5
        columnSpacing: 5
        Label { text: "Id" }
        SpinBox {
            value: taskId
            editable: true
            to: 9999
            onValueChanged: taskId = value
        }

        Label { text: "Title" }
        TextField {
            placeholderText: "Enter name"
            text: taskTitle
            selectByMouse: true
            Layout.fillWidth: true
            onTextChanged: taskTitle = text
        }

        Label { text: "Priority" }
        ComboBox {
            currentIndex: taskPriority
            model: ["Low", "Medium", "High"]
            onCurrentIndexChanged: taskPriority = currentIndex
        }

        Label { text: "Link" }
        TextField {
            placeholderText: "Enter link"
            text: taskLink
            selectByMouse: true
            Layout.fillWidth: true
            onTextChanged: taskLink = text
        }
    }
}
