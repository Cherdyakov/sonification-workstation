import QtQuick 2.7
import "ItemCreation.js" as Code

Image {
    id: paletteItem

    property string componentFile
    property string image

    source: image

    width: 50
    height: 50

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
