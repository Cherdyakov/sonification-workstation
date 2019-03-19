import QtQuick 2.7
import "Style.js" as Style

Text {
    id: label
    text: "Value: "
    font.pointSize: Style.editorFontSize
    color: Style.editorTextColor
    horizontalAlignment: Text.AlignLeft
}
