import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.11
import "Style.js" as Style

SowParameter {
    id: root

    // Fixed (user supplied) value toggle
    ColumnLayout {
        id: fixed
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

}
