import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "Style.js" as Style

Rectangle {
    id: rect
    z: 300
    x: Style.editorMargin / 2
    y: Style.editorMargin / 2
    height: childrenRect.height + Style.editorMargin
    width: childrenRect.width + Style.editorMargin
    radius: Style.editorRadius
    anchors.centerIn: parent
    color: mute ? Style.itemMuteColor : mainColor
    opacity: 0
    enabled: false
}
