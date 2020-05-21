import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.13

Window {
    id: window
    visible: true
    width: 200
    height: 600
    x: 100
    y: 100
    title: qsTr("Prototype Manager")

    Column {
        id: column1

        ListModel {
            id: contactModel
            ListElement {
                name: "Window 1"
                qmlfile: "Window1.qml"
                visible: false
            }
            ListElement {
                name: "Window 2"
                qmlfile: "Window2.qml"
                visible: false
            }
        }

        Column {
            width: window.width
            height: 200
            spacing: 10
            Repeater {
                model: contactModel
                delegate: Rectangle {
                    width: parent.width
                    height: 30
                    color: model.visible ? "green" : "pink"

                    Text {
                        anchors.centerIn: parent
                        text: name
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            var win = model.win;
                            console.log("model window", win);
                            if (win) {
                                win.close();
                                model.win = null;
                                model.visible = false;
                                return;
                            }

                            var component = Qt.createComponent(qmlfile);
                            win = component.createObject(window);
                            model.win = win;
                            model.visible = true;
                            win.x = (Screen.desktopAvailableWidth - win.width) / 2
                            win.y = (Screen.desktopAvailableHeight - win.height) / 2
                            win.show();
                        }
                    }


                }
            }

        }



    }



}

/*##^##
Designer {
    D{i:4;anchors_x:200}
}
##^##*/
