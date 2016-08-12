import QtQuick 2.0
import "itemCreation.js" as Code

Image {
    id: paletteItem

    property string componentFile
    property string image

    source: image

    MouseArea {
        anchors.fill: parent

        onPressed: Code.startDrag(mouse);
        onPositionChanged: Code.continueDrag(mouse);
        onReleased: Code.endDrag(mouse);
    }
}
