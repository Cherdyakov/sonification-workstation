import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.11
import "Style.js" as Style

Rectangle {
    id: rect
    z: 300
    height: childrenRect.height + Style.editorMargin
    width: childrenRect.width + Style.editorMargin
    radius: Style.editorRadius
    anchors.centerIn: parent
    color: mute ? Style.itemMuteColor : mainColor
    opacity: 0
    enabled: false
}
