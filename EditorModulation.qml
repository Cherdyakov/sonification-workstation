import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import "Style.js" as Style

ColumnLayout {
    id: root
    Layout.maximumHeight: Style.editorRowHeight * 2

    property alias modLabel: modLabel
    property alias depthLabel: depthLabel
    property alias spinBox: spinBox
    property alias comboBox: comboBox

    property var modulationTypes: [qsTr("Amplitude"),
                                   qsTr("Frequency")]

    signal modulationChanged(string modulation)
    signal depthValueChanged(double depthValue)

    RowLayout {
        id: row1
        EditorLabel {
            id: modLabel
            text: qsTr("Modulation: ")
            Layout.maximumHeight: Style.editorRowHeight
            Layout.fillWidth: true
        }
        EditorComboBox {
            id: comboBox
            model: modulationTypes
            Layout.maximumHeight: Style.editorRowHeight
            Layout.fillWidth: true
            onCurrentTextChanged: modulationChanged(comboBox.currentText)
        }
    }

    RowLayout {
        id: row2
        EditorLabel {
            id: depthLabel
            text: qsTr("Depth: ")
            Layout.maximumHeight: Style.editorRowHeight
            Layout.fillWidth: true
        }
        EditorDoubleSpinBox {
            id: spinBox
            Layout.maximumHeight: Style.editorRowHeight
            Layout.preferredWidth: Style.editorControlWidth
            onValueChanged: depthValueChanged(spinBox.value / 100)
        }
    }

}
