import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import "Style.js" as Style

ColumnLayout {
    id: root
    Layout.maximumHeight: Style.editorRowHeight * 6
    property alias label: label
    property alias lowLabel: lowLabel
    property alias highLabel: highLabel
    property alias low: lowSpinBox.doubleValue
    property alias high: highSpinBox.doubleValue
    property alias exponent: expSpinBox.doubleValue
    property alias scaled: checkBox.checked
    property alias lowFrom: lowSpinBox.doubleFrom
    property alias lowTo: lowSpinBox.doubleTo
    property alias lowStepSize: lowSpinBox.doubleStepSize
    property alias highFrom: highSpinBox.doubleFrom
    property alias highTo: highSpinBox.doubleTo
    property alias highStepSize: highSpinBox.doubleStepSize

    RowLayout {
        EditorLabel {
            id: label
            text: qsTr("Frequncey Scaling: ")
            Layout.maximumHeight: Style.editorRowHeight
            Layout.preferredWidth: Style.editorLabelWidth
            Layout.fillWidth: true
        }

        CheckBox {
            id: checkBox
        }
    }

    RowLayout {
        EditorLabel {
            id: lowLabel
            text: qsTr("Low: ")
            Layout.maximumHeight: Style.editorRowHeight
            Layout.fillWidth: true
        }

        EditorDoubleSpinBox {
            id: lowSpinBox
            Layout.maximumHeight: Style.editorRowHeight
            Layout.preferredWidth: Style.editorControlWidth
            onDoubleValueChanged: lowChanged(doubleValue)
        }
    }
    RowLayout {
        EditorLabel {
            id: highLabel
            text: qsTr("High: ")
            Layout.maximumHeight: Style.editorRowHeight
            Layout.fillWidth: true
        }

        EditorDoubleSpinBox {
            id: highSpinBox
            Layout.maximumHeight: Style.editorRowHeight
            Layout.preferredWidth: Style.editorControlWidth
            onDoubleValueChanged: highChanged(doubleValue)
        }
    }
    RowLayout {
        EditorLabel {
            id: expLabel
            text: qsTr("Scaling Exponent: ")
            Layout.maximumHeight: Style.editorRowHeight
            Layout.fillWidth: true
        }

        EditorDoubleSpinBox {
            id: expSpinBox
            doubleFrom: 1
            doubleTo: 6400
            doubleStepSize: 1
            Layout.maximumHeight: Style.editorRowHeight
            Layout.preferredWidth: Style.editorControlWidth
            onDoubleValueChanged: exponentChanged(doubleValue)
        }
    }
}
