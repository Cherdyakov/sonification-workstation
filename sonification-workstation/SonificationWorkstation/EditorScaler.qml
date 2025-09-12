import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
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

            Accessible.ignored: true
        }
    }

    RowLayout {
        EditorLabel {
            id: lowLabel
            text: qsTr("Scale Low: ")
        }

        EditorDoubleSpinBox {
            id: lowSpinBox
            Accessible.ignored: true
        }
    }
    RowLayout {
        EditorLabel {
            id: highLabel
            text: qsTr("Scale High: ")
        }

        EditorDoubleSpinBox {
            id: highSpinBox
            Accessible.ignored: true
        }
    }
    RowLayout {
        EditorLabel {
            id: expLabel
            text: qsTr("Scale Exponent: ")
        }

        EditorDoubleSpinBox {
            id: expSpinBox
            Accessible.ignored: true
            from: 100
            to: 6400
//            stepSize: 10
        }
    }
}
