import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.0

Item {

    Window {
        id: synthWindow
        visible: true
        width: 640
        height: 480
        title: qsTr("Sonification Workstation: Synthesis")
    }

    Window {
        id: dataWindow
        visible: false
        width: 640
        height: 480
        title: qsTr("Sonification Workstation: Data")
    }


}

