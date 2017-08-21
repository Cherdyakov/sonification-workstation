import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import "Style.js" as Style

ColumnLayout {
    id: root
    Layout.maximumHeight: Style.editorRowHeight * 2

    property alias label: label
    property alias spinBox: spinBox

    signal paramValueChanged(double value)

    EditorLabel {
        id: label
        text: qsTr("Value: ")
        Layout.maximumHeight: Style.editorRowHeight
        Layout.fillWidth: true
    }

    EditorDoubleSpinBox {
        id: spinBox
        Layout.maximumHeight: Style.editorRowHeight
        Layout.preferredWidth: Style.editorControlWidth
        onValueChanged: paramValueChanged(spinBox.realValue)
    }

}
