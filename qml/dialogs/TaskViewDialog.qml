import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import Timelogger 1.0

import "../controls"

Dialog {
    property variant task

    width: parent.width - 20
    height: parent.height - 20
    x: (parent.width - width) / 2
    y: (parent.height - height) / 2
    standardButtons: Dialog.Ok | Dialog.Cancel


    TaskDialog {
        taskId: task.id
        taskTitle: task.title
        taskPriority: task.priority
        taskLink: task.link

        id: editTaskDialog
        modal: true

        onAccepted: taskManager.changeTask(taskId, taskTitle, taskLink, taskPriority)
    }


    GridLayout {
        columns: 2
        anchors.fill: parent
        anchors.margins: 10
        rowSpacing: 5
        columnSpacing: 5

        Row {
            Layout.column: 0
            Layout.row: 0
            Layout.columnSpan: 2
            spacing: 1
             Button {
                 text: "Edit"
                 onClicked: {
                     editTaskDialog.open()
                 }
             }
             Button {
                 text: "Remove"
                 onClicked: {
                     taskManager.removeTask(task.id)
                     close()
                 }
             }
        }

        Label { text: "Id" }
        Label { text: task.id }

        Label { text: "Title" }
        Label { text: task.title }

        Label { text: "Priority" }
        Label { text: task.priorityStr }

        Label { text: "Link" }
        Label {
            text: ("<a href='"+task.link+"'>"+task.link+"</a>")
            onLinkActivated:{
                Qt.openUrlExternally(task.link)
            }
        }

        Label { text: "Status" }
        Label { text: task.statusStr }

        Label { text: "Notes" }
        BorderTextEdit {
            textValue: task.notes
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
