import QtQuick 2.7


DropArea {
    id: dropArea

    height: 120; width: 120

    onEntered: console.log("enter")
    onExited: console.log("exit")
    onDropped: console.log("drop")

    Rectangle {
        id: rect
        anchors.fill: parent
        color: "grey"
        border.color: "black"
        border.width: 4

    }

}
