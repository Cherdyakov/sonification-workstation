import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.11
import "Style.js" as Style

Item {
    id: root

    width: childrenRect.width
    height: childrenRect.height

    property alias name: layout.title
    property alias value: parameter.value
    property alias fixed: fixed.fixed
    property alias mapping: mapper.text
    property alias scaled: scaler.scaled
    property alias scaleLow: scaler.low
    property alias scaleHigh: scaler.high
    property alias scaleExp: scaler.exponent

    EditorLayout {
        id: layout
        title: label

        RowLayout {

            EditorDoubleParam {
                id: parameter
                label.text: "Parameter: "
            }

            EditorFixedParam {
                id: fixed
                label.text: qsTr("Fixed: ")
            }
        }

        EditorMapper {
            id: mapper
            label.text: qsTr("Parameter Source: ")
            maxIndexes: 128

        }

        EditorScaler {
            id: scaler
            label.text: qsTr("Scaled: ")
            lowLabel.text: qsTr("Scale Low: ")
            highLabel.text: qsTr("Scale High: ")
        }
    }

}
