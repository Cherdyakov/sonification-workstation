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

    // For setting properties of the SpinBoxes.
    property alias lowSpinBox: lowSpinBox
    property alias highSpinBox: highSpinBox
    property alias expSpinBox: expSpinBox

    RowLayout {

        EditorLabel {
            id: label
            text: qsTr("Scaled: ")
            horizontalAlignment: Text.AlignRight
        }

        CheckBox {
            id: checkBox
            implicitHeight: Style.editorRowHeight
            implicitWidth: implicitHeight

            indicator: Rectangle {

                implicitHeight: Style.editorRowHeight
                implicitWidth: implicitHeight

                Rectangle {
                    width: parent.width - 4
                    height: parent.height - 4
                    x: 2
                    y: 2
                    color: checkBox.down ? "grey" : "black"
                    visible: checkBox.checked
                }
            }
        }
    }

    RowLayout {
        EditorLabel {
            id: lowLabel
            text: qsTr("Scale Low: ")
        }

        EditorDoubleSpinBox {
            id: lowSpinBox
        }
    }
    RowLayout {
        EditorLabel {
            id: highLabel
            text: qsTr("Scale High: ")
        }

        EditorDoubleSpinBox {
            id: highSpinBox
        }
    }
    RowLayout {
        EditorLabel {
            id: expLabel
            text: qsTr("Scale Exponent: ")
        }

        EditorDoubleSpinBox {
            id: expSpinBox
            from: 100
            to: 6400
//            stepSize: 10
        }
    }
}
