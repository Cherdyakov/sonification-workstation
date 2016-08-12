import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.0

ApplicationWindow {

    id: synthWindow

    width: 640
    height: 480
    visible: true
    title: qsTr("Sonification Workstation: Synthesis")

    menuBar: MenuBar {
        id: menuBar
        Menu {
            title: "File"
            MenuItem {
                text: "Exit"
                onTriggered:  {
                    quit()
                    console.log("click")
                }

            }
        }
    }

    statusBar: StatusBar {
        id: statusBar
    }

    Item {

        id: window
        anchors.fill: parent

        // top panel
        Rectangle {
            id: toolbox

            height: 70
            color: "gray"
            anchors { right: parent.right; top: parent.top; left: parent.left}

                    Row {
                        id: palette
                        anchors.centerIn: parent
                        spacing: 8

                        PaletteItem {
                            anchors.verticalCenter: parent.verticalCenter
                            componentFile: "OscillatorGUI.qml"
                            source: "images/oscIcon.png"
                            image: "images/oscIcon.png"
                        }
                    }
        }


        ScrollView {
            id: workspace

            anchors {
                fill: parent
            }

            DropArea {
                anchors.fill: parent
            }

        }
    }


}
