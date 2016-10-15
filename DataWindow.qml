import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.0

ApplicationWindow {

    width: 640
    height: 480
    visible: true
    title: qsTr("Sonification Workstation: Data")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Exit")
                onTriggered: quit()
            }
        }
    }

    statusBar: StatusBar {
        id: statusBar
    }
}
