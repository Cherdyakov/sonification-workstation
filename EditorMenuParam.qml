import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
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
    EditorComboBox {
        id: comboBox
        model: [qsTr("First"), qsTr("Second"), qsTr("Third")]
        Layout.maximumHeight: Style.editorRowHeight
        Layout.fillWidth: true
    }
}
