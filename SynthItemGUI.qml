import QtQuick 2.0

Item {
    id: root

    property int type: -1
    //OUT = 0
    //OSC = 1
    property bool created: false
    property string label: "SON"
    property string mainColor
    property string textColor
    property var children: new Array

    function create() {
        created = true
        graph.createItem(this, type)
        synthWindow.synthItems.push(this)
        dac.children.push(this)
        canvas.requestPaint()
    }

    width: 64; height: 64

    onXChanged: canvas.requestPaint()
    onYChanged: canvas.requestPaint()

    Rectangle {
        id: rect
        z: 200
        anchors.fill: parent
        radius: 10
        color: mainColor
        opacity: created ? 1 : 0.4

        border.width: 0
        border.color: textColor


        MouseArea {
            anchors.fill: parent
            drag.target: root
            drag.axis: Drag.XAndYAxis
            drag.minimumX: 0
            drag.minimumY: 0

            onDoubleClicked: {

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

}
