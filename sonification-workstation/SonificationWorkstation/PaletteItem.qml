import QtQuick 2.12
import QtQuick.Window 2.12
import "ItemCreation.js" as Code
import "Style.js" as Style

Image {
    id: paletteItem

    property string componentFile
    property string image

    source: image

    width: Style.paletteItemDiameter * Screen.devicePixelRatio
    height: Style.paletteItemDiameter * Screen.devicePixelRatio

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
