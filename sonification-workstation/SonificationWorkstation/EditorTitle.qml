import QtQuick 2.12
import QtQuick.Layouts 1.11
import "Style.js" as Style

Text {
    id: title
    text: qsTr("ITEM")
    font.pointSize: Style.editorTitleSize
    color: Style.itemTextColor
    Layout.alignment: Layout.Center
    Layout.maximumHeight: 12
    horizontalAlignment: Text.AlignHCenter
}
