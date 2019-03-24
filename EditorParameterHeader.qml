import QtQuick 2.12
import "Style.js" as Style

Text {
    id: label
    text: "Parameter"
    color: Style.editorTextColor
    horizontalAlignment: Text.AlignHCenter
    font.pointSize: Style.editorParameterHeaderFontSize
//    font.bold: true
}
