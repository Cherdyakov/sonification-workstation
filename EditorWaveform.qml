import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import "Style.js" as Style

RowLayout {
    id: root
    Layout.maximumHeight: Style.editorRowHeight

    signal waveformChanged(int form)

    EditorLabel {
        id: label
        text: "Waveform: "
        Layout.maximumHeight: Style.editorRowHeight
        Layout.preferredWidth: Style.editorLabelWidth
    }
    EditorComboBox {
        id: comboBox
        model: ["Sine", "Saw", "Square"]
        Layout.maximumHeight: Style.editorRowHeight
        Layout.preferredWidth: Style.editorControlWidth

        onCurrentIndexChanged: waveformChanged(comboBox.currentIndex)
    }
}
