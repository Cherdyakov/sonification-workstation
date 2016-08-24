import QtQuick 2.7


Item {

    id: root

    property int type: -1
    //OUT = 0
    //OSC = 1
    property bool created: false
    property var inputs: new Array
    property var outputs: new Array
    property string label: "SON"
    property string mainColor
    property string textColor
    property alias patchOut: patchOut
    property alias patchIn: patchIn

    function create() {
        created = true
        graph.createItem(this, type)
        canvas.requestPaint()
    }

    function acceptConnection(SynthItem) {
        //or something...
    }


    width: 72; height: 64

    onXChanged: canvas.requestPaint()
    onYChanged: canvas.requestPaint()

    FocusScope {
        id: scope
        anchors.fill: parent
    }

    PatchPoint {
        id: patchIn
        anchors {
            top: root.top
            bottom: root.bottom
            left: root.left
        }
        state: "UNCONNECTED"
    }

    PatchPoint {
        id: patchOut
        anchors {
            top: root.top
            bottom: root.bottom
            right: root.right
        }
        state: "UNCONNECTED"
    }


    Rectangle {
        id: rect
        z: 200
        anchors {
            top: root.top
            bottom: root.bottom
            horizontalCenter: root.horizontalCenter
        }

        width: root.width * 0.8

        radius: 0
        color: mainColor
        opacity: created ? 1 : 0.4

        border.width: 0
        border.color: textColor


        MouseArea {
            id: mouseArea

            anchors.fill: rect

            drag.target: root
            drag.axis: Drag.XAndYAxis
            drag.minimumX: 0
            drag.minimumY: 0

            onClicked: {
                scope.forceActiveFocus()
            }

        }

        Text {
            id: labelText
            text: label
            color: textColor
            anchors {
                centerIn: parent
            }
        }

    }

    Keys.onPressed: {
        if (event.key == Qt.Key_Backspace || event.key == Qt.Key_Delete) {
            console.log("Type: Back!")
            var i = synthWindow.synthItems.indexOf(this)
            synthWindow.synthItems.splice(i, 1)
            this.destroy()
            event.accepted = true;
        }
    }

}

