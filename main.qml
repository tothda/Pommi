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
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        CheckBox {
            id: checkBox
            text: qsTr("Check Box")
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
}
