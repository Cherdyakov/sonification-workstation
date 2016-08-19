import QtQuick 2.7
import "patchCreation.js" as Script


Rectangle {

    property bool connecting: false
    id: patchPoint
    state: "UNCONNECTED"
    z: 180
    radius: 8
    width: parent.width * 0.2

    states: [
        State {
            name: "UNCONNECTED"
            PropertyChanges {
                target: patchPoint; color: "white"
                connecting: false
            }
        },

        State {
            name: "CONNECTED"
            PropertyChanges {
                target:patchPoint; color: "chartreuse"
                connecting: false
            }
        },

        State {
            name: "CONNECTING"
            PropertyChanges {
                target:patchPoint; color: "chartreuse"
                connecting: true
            }
            PropertyChanges {
                target: synthWindow; connecting: true
            }

        }
    ]

    MouseArea {
        id: mouseArea

        anchors.fill: parent

        onClicked: {
            patchPoint.state = "CONNECTING"
            Script.createConnection()

        }

    }

}

