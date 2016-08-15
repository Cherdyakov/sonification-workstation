import QtQuick 2.0

Item {
    id: root

    property bool created: false
    property string label: "SON"
    property string mainColor
    property string textColor

    function create() {
        created = true
        graph.createItem(graph.OSCILLATOR)
    }

    width: 64; height: 64


    Rectangle {
        id: rect
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
