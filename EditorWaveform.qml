import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import "Style.js" as Style

RowLayout {
    id: root
    Layout.maximumHeight: Style.editorRowHeight

    property alias label: label
    property alias comboBox: comboBox

    signal waveformChanged(int form)

    EditorLabel {
        id: label
        text: "Waveform: "
        Layout.maximumHeight: Style.editorRowHeight
        Layout.fillWidth: true
    }
    EditorComboBox {
        id: comboBox
        model: ["Sine", "Saw", "Square"]
        Layout.maximumHeight: Style.editorRowHeight
        Layout.maximumWidth: Style.editorControlWidth

        onCurrentIndexChanged: waveformChanged(comboBox.currentIndex)
    }
}
