import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.13

Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Column {
        id: column
        width: 200
        height: 182
        anchors.verticalCenterOffset: -77
        anchors.horizontalCenterOffset: -186
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        CheckBox {
            id: control
            text: qsTr("Check Box")
            wheelEnabled: false
            checked: true
            display: AbstractButton.TextBesideIcon

            indicator: Rectangle {
                implicitWidth: 20
                implicitHeight: 20
                x: control.leftPadding
                y: parent.height / 2 - height / 2
                radius: 6
                border.color: control.down ? "#17a81a" : "#21be2b"

                Rectangle {
                    width: 10
                    height: 10
                    x: (parent.implicitWidth - width) / 2
                    y: (parent.implicitHeight - height) / 2
                    radius: 2
                    color: control.down ? "#17a81a" : "#21be2b"
                    visible: control.checked
                }
            }

            contentItem: Text {
                text: control.text
                font: control.font
                opacity: enabled ? 1.0 : 0.3
                color: control.down ? "#17a81a" : "#21be2b"
                verticalAlignment: Text.AlignVCenter
                leftPadding: control.indicator.width + control.spacing
            }
        }

        CheckBox {
            id: checkBox1
            text: qsTr("Check Box")
        }

        CheckBox {
            id: checkBox2
            text: qsTr("Check Box")
        }

    }


    ListView {
        x: 200
        y: 24
        width: 110
        height: 160
        delegate: Text {
            text: "index: " + index + " title: " + title;
        }
        model: task_list
    }


    ListView {
        x: 400
        y: 24
        width: 110
        height: 160
        delegate: TextEdit {
            text: title
            readOnly: false
            selectByKeyboard: true
            selectByMouse: true
            onEditingFinished: title = text
        }
        model: task_list
    }
}
