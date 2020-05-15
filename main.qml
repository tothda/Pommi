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
        anchors.leftMargin: 200
        anchors.fill: parent
        spacing: 10
        //        interactive: false

        delegate:
            TextInput {
            text: title
            readOnly: false
            selectByMouse: true
            onEditingFinished: title = text

            Rectangle {
                anchors.fill: parent
                color: "yellow"
                opacity: 0.1
            }
        }

        model: task_list

    }


}

/*##^##
Designer {
    D{i:8;anchors_x:200}
}
##^##*/
