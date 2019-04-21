import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.11
import "Style.js" as Style

ColumnLayout {
    id: root
    Layout.maximumHeight: Style.editorRowHeight * 2

    property alias label: label
    property alias checkBox: checkBox
    property alias fixed: checkBox.checked

    EditorLabel {
        id: label
        text: qsTr("Fixed: ")
        height: Style.editorRowHeight
    }
    CheckBox {
        id: checkBox
    }
}
