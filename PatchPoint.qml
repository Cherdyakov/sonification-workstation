import QtQuick 2.7
import "patchCreation.js" as Script


Rectangle {

    id: patchPoint
    property bool connecting: false
    state: "UNCONNECTED"
    z: 180
    radius: 8
    width: parent.width * 0.2


    states: [
        State {
            name: "UNCONNECTED"
            PropertyChanges {
                target: patchPoint;
                color: "white"
                connecting: false
            }
        },

        State {
            name: "CONNECTED"
            PropertyChanges {
                target:patchPoint;
                color: "chartreuse"
                connecting: false
            }
        },

        State {
            name: "CONNECTING"
            PropertyChanges {
                target:patchPoint;
                color: "chartreuse"
                connecting: true
            }
        }
    ]

    MouseArea {
        id: mouseArea

        anchors.fill: parent

        onClicked: {
            state = "CONNECTING"
            var patch = Script.createPatch()
            console.log("patch returned: " + patch)
            patch.start = patchPoint
            patch.myCanvas = canvas
            patchManager.patches.push(patch)
            console.log(patchPoint.color)

        }

    }


}

