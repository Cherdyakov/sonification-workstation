import QtQuick 2.12
import QtQuick.Layouts 1.11
import "Style.js" as Style

Text {
    id: label
    text: "Value: "
    font.pointSize: Style.editorFontSize
    color: Style.editorTextColor
    horizontalAlignment: Text.AlignLeft   
    Layout.maximumHeight: Style.editorRowHeight
    Layout.fillWidth: true
}
