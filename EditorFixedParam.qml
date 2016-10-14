import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import "Style.js" as Style

RowLayout {
    id: root
    Layout.maximumHeight: Style.editorRowHeight

    property alias label: label
    property alias checkBox: checkBox

    signal fixedChanged(bool fixed)

    EditorLabel {
        id: label
        text: "Fixed: "
        Layout.maximumHeight: Style.editorRowHeight
        Layout.preferredWidth: Style.editorLabelWidth
        Layout.fillWidth: true
    }
    CheckBox {
        id: checkBox
        height: Style.editorRowHeight
        Layout.maximumHeight: Style.editorRowHeight

        onCheckedChanged: fixedChanged(checkBox.checked)
    }
}
