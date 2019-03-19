import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.11
import "Style.js" as Style

ColumnLayout {
    id: root
    Layout.maximumHeight: Style.editorRowHeight * 6

    property alias label: label
    property alias lowLabel: lowLabel
    property alias highLabel: highLabel
    property alias scaled: checkBox.checked
    property alias low: lowSpinBox.value
    property alias realLow: lowSpinBox.realValue
    property alias high: highSpinBox.value
    property alias realHigh: highSpinBox.realValue
    property alias exp: expSpinBox.value
    property alias realExp: expSpinBox.realValue

    RowLayout {
        EditorLabel {
            id: label
            text: qsTr("Scaled: ")
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
            text: qsTr("Scale Low: ")
            Layout.maximumHeight: Style.editorRowHeight
            Layout.fillWidth: true
        }

        EditorDoubleSpinBox {
            id: lowSpinBox
            Layout.maximumHeight: Style.editorRowHeight
            Layout.preferredWidth: Style.editorControlWidth
        }
    }
    RowLayout {
        EditorLabel {
            id: highLabel
            text: qsTr("Scale High: ")
            Layout.maximumHeight: Style.editorRowHeight
            Layout.fillWidth: true
        }

        EditorDoubleSpinBox {
            id: highSpinBox
            Layout.maximumHeight: Style.editorRowHeight
            Layout.preferredWidth: Style.editorControlWidth
        }
    }
    RowLayout {
        EditorLabel {
            id: expLabel
            text: qsTr("Scale Exponent: ")
            Layout.maximumHeight: Style.editorRowHeight
            Layout.fillWidth: true
        }

        EditorDoubleSpinBox {
            id: expSpinBox
            from: 100
            to: 6400
            stepSize: 10
            Layout.maximumHeight: Style.editorRowHeight
            Layout.preferredWidth: Style.editorControlWidth
        }
    }
}
