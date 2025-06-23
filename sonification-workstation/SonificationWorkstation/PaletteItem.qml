import QtQuick 2.12
import QtQuick.Window 2.12
import "ItemCreation.js" as Code
import "Style.js" as Style

Rectangle {

    id: paletteItem
    // Name of SynthItem, e.g. "OSC"
    property var label
    // QML file to load when creating item
    property var componentFile
    // Physical properties of this item on the Palette
    property var textColor: themeManager.themeMap["textColor"]
    border.color: textColor
    border.width: Style.itemBorderWidth * Screen.pixelDensity
    color: themeManager.themeMap[label]
    width: Style.itemDiameter * Screen.pixelDensity
    height: Style.itemDiameter * Screen.pixelDensity
    radius: width * 0.5

    signal itemCreated(var item)

    Text {
        text: label
        color: textColor
        font.pointSize: Style.editorFontSize
        anchors {
            centerIn: parent
        }
    }

    MouseArea {
        anchors.fill: parent

        onPressed: (mouse)=> {
            var item = Code.startDrag(mouse)
            itemCreated(item)
        }
        onPositionChanged: Code.continueDrag(mouse)
        onReleased: Code.endDrag(mouse)
    }
}
