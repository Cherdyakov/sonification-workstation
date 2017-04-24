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
    property alias checkBox: checkBox
    property alias lowSpinBox: lowSpinBox
    property alias highSpinBox: highSpinBox
    property alias expSpinBox: expSpinBox

    signal useScalingChanged(bool scaling)
    signal lowChanged(double low)
    signal highChanged(double high)
    signal exponentChanged(double exp)

    Connections {
        target: fileReader
        onQmlDatasetChanged: {
            // maybe?
        }
    }

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
            onCheckedChanged: useScalingChanged(checkBox.checked)
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
            onValueChanged: lowChanged(lowSpinBox.value / 100)
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
            onValueChanged: highChanged(highSpinBox.value / 100)
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
            Layout.maximumHeight: Style.editorRowHeight
            Layout.preferredWidth: Style.editorControlWidth
            onValueChanged: exponentChanged(expSpinBox.value / 100)
        }
    }
}
