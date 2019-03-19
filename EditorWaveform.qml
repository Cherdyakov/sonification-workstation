import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.11
import "Style.js" as Style

ColumnLayout {
    id: root
    Layout.maximumHeight: Style.editorRowHeight * 2

    property alias label: label
    property alias comboBox: comboBox
    property  alias model: comboBox.model

    signal waveformChanged(int form)

    EditorLabel {
        id: label
        text: qsTr("Waveform: ")
        Layout.maximumHeight: Style.editorRowHeight
        Layout.fillWidth: true
    }
    EditorComboBox {
        id: comboBox
        model: [qsTr("Sine"), qsTr("Saw"), qsTr("Square")]
        Layout.maximumHeight: Style.editorRowHeight
        Layout.fillWidth: true
        onCurrentIndexChanged: waveformChanged(comboBox.currentIndex)
    }
}
