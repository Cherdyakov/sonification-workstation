import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import "Style.js" as Style

Rectangle {
    id: rect
    z: 300
    height: childrenRect.height
    width: childrenRect.width
    radius: Style.editorRadius
    anchors.centerIn: parent
    color: Style.editorBackgroundColor
    opacity: 0

}
