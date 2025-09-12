import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "Style.js" as Style

ColumnLayout {
    id: root
    Layout.maximumHeight: Style.editorRowHeight * 2

    property alias label: label
    property alias comboBox: comboBox
    property alias model: comboBox.model
    property alias index: comboBox.currentIndex

    EditorLabel {
        id: label
        text: qsTr("Select: ")
        Layout.maximumHeight: Style.editorRowHeight
        Layout.fillWidth: true
    }
}
