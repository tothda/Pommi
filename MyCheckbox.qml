import QtQuick 2.0
import QtQuick.Controls 2.13

Item {
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
}
