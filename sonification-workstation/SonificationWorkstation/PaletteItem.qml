import QtQuick 2.12
import "ItemCreation.js" as Code

Image {
    id: paletteItem

    property string componentFile
    property string image

    source: image

    width: 34
    height: 34

    signal itemCreated(var item)

    MouseArea {
        anchors.fill: parent

        onPressed: {
            var item = Code.startDrag(mouse)
            itemCreated(item)
        }
        onPositionChanged: Code.continueDrag(mouse)
        onReleased: Code.endDrag(mouse)
    }
}
