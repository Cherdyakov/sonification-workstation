import QtQuick 2.12
import QtQuick.Layouts 1.11
import "Style.js" as Style

ColumnLayout {

    property alias title: title.text

    x: Style.editorMargin / 2
    y: Style.editorMargin / 2

    Text {
        id: title
        text: qsTr("ITEM")
        font.pointSize: Style.editorTitleSize
        color: Style.itemTextColor
        Layout.alignment: Layout.Center
        Layout.maximumHeight: 12
        horizontalAlignment: Text.AlignHCenter
    }

}
