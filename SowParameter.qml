import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.11
import "Style.js" as Style

Item {
    id: root

    EditorLayout {
        id: layout
        title: label

        RowLayout {

            EditorDoubleParam {
                id: parameterEditor
                label.text: "Parameter: "
                onValueChanged: {
                    if(implementation !== null) {
                        implementation.setFreq(value)
                    }
                }
            }

            EditorFixedParam {
                id: fixedEditor
                label.text: qsTr("Fixed: ")
                onFixedChanged: {
                    if(implementation !== null) {
                        implementation.setFreqFixed(fixed)
                    }
                }
            }
        }

        EditorMapper {
            id: mapper
            label.text: qsTr("Parameter Source: ")
            maxIndexes: 128
            onMappingsChanged:
            {
                var implementationMappings = mappings.map(function(value) {
                    return value - 1
                } )
                if(implementation !== null) {
                    implementation.setFreqIndexes(implementationMappings)
                }
            }
        }

        EditorScaler {
            id: scaler
            label.text: qsTr("Scaled: ")
            lowLabel.text: qsTr("Scale Low: ")
            highLabel.text: qsTr("Scale High: ")

            onLowChanged: { implementation.setFreqScaleLow(low) }
            onHighChanged:{ implementation.setFreqScaleHigh(high) }
            onExponentChanged: { implementation.setFreqScaleExponent(exponent) }
            onScaledChanged: { implementation.setFreqScaled(scaled) }
        }
    }
}
