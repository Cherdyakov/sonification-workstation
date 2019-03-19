import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.11
import "Style.js" as Style

Item {
    id: root

    width: childrenRect.width
    height: childrenRect.height

    property alias itemName: layout.title
    property alias paramName: label.text
    property alias value: spinBox.value
    property alias realValue: spinBox.realValue
    property alias fixed: fixed.fixed
    property alias map: mapper.text
    property alias scaled: scaler.scaled
    property alias scaleLow: scaler.low
    property alias scaleRealLow: scaler.realLow
    property alias scaleHigh: scaler.high
    property alias scaleRealHigh: scaler.realHigh
    property alias scaleExp: scaler.exp
    property alias scaleRealExp: scaler.realExp
    property alias mapper: mapper

    EditorLayout {
        id: layout

        RowLayout {

            ColumnLayout {
                Layout.maximumHeight: Style.editorRowHeight * 2

                EditorLabel {
                    id: label
                    Layout.maximumHeight: Style.editorRowHeight
                    Layout.fillWidth: true
                }

                EditorDoubleSpinBox {
                    id: spinBox
                    Layout.maximumHeight: Style.editorRowHeight
                    Layout.preferredWidth: Style.editorControlWidth
                }

            }

            EditorFixed {
                id: fixed
            }
        }

        EditorMapper {
            id: mapper
            maxIndexes: 128
        }

        EditorScaler {
            id: scaler
        }
    }

}
