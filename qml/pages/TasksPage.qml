import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import Timelogger 1.0

import "../controls"
import "../dialogs"

Page {
    width: 600
    height: 400

    header: RowLayout {
        Label {
            text: qsTr("Tasks")
            font.pixelSize: Qt.application.font.pixelSize * 2
            padding: 10
            Layout.fillWidth: true
        }
        CheckBox {
            id: underReviewVisible
            text: "Show under review list"
        }
        CheckBox {
            id: doneVisible
            text: "Show done list"
        }

        ToolButton {
            text: "Create task"
            onClicked: {
                newTaskDialog.clearTaskValues()
                newTaskDialog.open()
            }
        }
    }

    TaskDialog {
        id: newTaskDialog
        modal: true

        onAccepted: taskManager.addTask(taskId, taskTitle, taskLink, taskPriority)
    }

    TaskViewDialog {
        id: viewTaskDialog
        modal: true
    }

    GridLayout {
        anchors.fill: parent
        anchors.margins: 30
        columns: 2

        Label {
            Layout.row: 0
            Layout.column: 0
            text: "Not started"
        }
        Label {
            Layout.row: 0
            Layout.column: 1
            text: "In progress"
        }

        TaskList {
            Layout.row: 1
            Layout.column: 0
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignCenter

            taskStatus: Task.NotStarted
            onTaskClickedToView: {
                viewTaskDialog.task = task
                viewTaskDialog.open()
            }
        }

        TaskList {
            Layout.row: 1
            Layout.column: 1
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignCenter

            taskStatus: Task.InProgress

            onTaskClickedToView: {
                viewTaskDialog.task = task
                viewTaskDialog.open()
            }
        }

        Label {
            Layout.row: 2
            Layout.column: 0
            text: "Under review"

            visible: underReviewVisible.checkState == Qt.Checked
        }
        Label {
            Layout.row: 2
            Layout.column: 1
            text: "Done"

            visible: doneVisible.checkState == Qt.Checked
        }
        TaskList {
            Layout.row: 3
            Layout.column: 0
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignCenter

            taskStatus: Task.UnderReview
            onTaskClickedToView: {
                viewTaskDialog.task = task
                viewTaskDialog.open()
            }
            visible: underReviewVisible.checkState == Qt.Checked
        }
        TaskList {
            Layout.row: 3
            Layout.column: 1
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignCenter

            taskStatus: Task.Done
            onTaskClickedToView: {
                viewTaskDialog.task = task
                viewTaskDialog.open()
            }
            visible: doneVisible.checkState == Qt.Checked
        }
    }
}
