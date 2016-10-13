import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import "Style.js" as Style

RowLayout {
    id: root
    Layout.maximumHeight: Style.editorRowHeight

    signal frequencyChanged(double freq)

    EditorLabel {
        id: label
        text: "Frequency: "
        Layout.maximumHeight: Style.editorRowHeight
    }

    EditorDoubleSpinBox {
        id: spinBox
        Layout.maximumHeight: Style.editorRowHeight
        onValueChanged: frequencyChanged(spinBox.value)
    }

}
