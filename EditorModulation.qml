import QtQuick 2.7
import SonLib 1.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import "Style.js" as Style

ColumnLayout {
    id: root
    Layout.maximumHeight: Style.editorRowHeight * 2

    property  alias depth: spinBox.doubleValue
    property alias modulation: comboBox.currentText

    property var modulationTypes: [qsTr("Amplitude"),
                                   qsTr("Frequency")]

    function modFromParameter(mod) {
        switch(mod) {
        case QtSynthItem.AMPLITUDE:
            comboBox.currentIndex = 0
            break
        case QtSynthItem.FREQUENCY:
            comboBox.currentIndex = 1
            break
        default:
            break
        }
    }

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
        }
    }

}
