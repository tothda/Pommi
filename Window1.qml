import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.13

Window {
    id: window
    visible: true
    width: 400
    height: 600
    title: qsTr("Hello World")
    property int headerHeight: 50
    property int footerHeight: 50

    Column {
        id: column1


        Rectangle {
            width: window.width
            height: window.headerHeight
            color: "yellow"
            Text {
                text: "Hello, I am Header!"
                anchors.centerIn: parent
            }
        }

        Rectangle {
            width: window.width
            height: window.height - window.headerHeight - window.footerHeight
            color: "lightblue"
            clip: true

            ListView {
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

                Component.onCompleted: {
                    console.log(task_list);
                }

            }
        }

        Rectangle {
            width: window.width
            height: window.footerHeight
            color: "beige"
            Text {
                text: "Hello, I am Footer!"
                anchors.centerIn: parent
            }

        }


    }



}

/*##^##
Designer {
    D{i:4;anchors_x:200}
}
##^##*/
