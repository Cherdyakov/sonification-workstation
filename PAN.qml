import QtQuick 2.7
import SonLib 1.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0
import "Style.js" as Style
import "SessionCode.js" as SessionCode

SynthItem {
    id: root
    label: qsTr("PAN")
    type: QtTransport.PANNER
    childType: QtSynthItem.INPUT
    mainColor: Style.panColor
    textColor: Style.itemTextColor

    Component.onCompleted: {
        create()
        panEditor.value = implementation.getPan();
        fixedEditor.fixed = implementation.getPanFixed();
        panScaler.low = implementation.getPanScaleLow();
        panScaler.high = implementation.getPanScaleHigh();
        panScaler.exponent = implementation.getPanScaleExponent();
        panScaler.scaled = implementation.getPanScaled();
    }

    // return json representation of self
    function read() {

        var parents = []
        for(var i = 0; i < synthParents.length; i++) {
            var parent = synthParents[i].identifier
            parents.push(parent)
        }

        var panIndexes = implementation.getPanIndexes()
        // remove keys from freqIndexes and store in js array
        var panIndexesArray = Object.keys(panIndexes).map(function(k) { return panIndexes[k] });

        var essence = {
            "identifier": identifier,
            "type": type,
            "x": x,
            "y": y,
            "muted": implementation.getMute(),
            "parents": parents,
            "pan": implementation.getPan(),
            "panIndexes": panIndexesArray,
            "panFixed": implementation.getPanFixed(),
            "panScaled": implementation.getPanScaled(),
            "panScaleLow": implementation.getPanScaleLow(),
            "panScaleHigh": implementation.getPanScaleHigh(),
            "panScaleExponent": implementation.getPanScaleExponent()

        }

        return essence
    }

    // initialize self from json
    function init(essence) {
        identifier = essence["identifier"]
        x = essence["x"]
        y = essence["y"]
        muted = essence["muted"]
        panEditor.value = essence["pan"]
        var indexes = essence["panIndexes"]
        var stringIndexes = SessionCode.indexesToString(indexes)
        panMapper.text = stringIndexes
        panMapper.validateMappings()
        fixedEditor.fixed = essence["panFixed"]
        panScaler.scaled = essence["panScaled"]
        panScaler.low = essence["panScaleLow"]
        panScaler.high = essence["panScaleHigh"]
        panScaler.exponent = essence["panScaleExponent"]
    }

    Editor {

        id: editor

        EditorLayout {
            id: layout
            title: label

            RowLayout {

                EditorDoubleParam {
                    id: panEditor
                    from: -1
                    to: 1
                    stepSize: 0.1
                    onValueChanged: {
                        implementation.setPan(value)
                    }
                }

                EditorFixedParam {
                    id: fixedEditor
                    label.text: qsTr("Fixed: ")
                    onFixedChanged: {
                        implementation.setPanFixed(fixed)
                    }
                }

            }

            EditorMapper {
                id: panMapper
                label.text: qsTr("Pan Source: ")
                onMappingsChanged:
                {
                    var implementationMappings = mappings.map(function(value) {
                        return value - 1
                    } )
                    if(implementation !== null) {
                        implementation.setPanIndexes(implementationMappings)
                    }
                }
            }

            EditorScaler {
                id: panScaler
                label.text: qsTr("Pan Scaling: ")
                lowLabel.text: qsTr("Pan Low: ")
                highLabel.text: qsTr("Pan High: ")
                lowFrom: -1
                lowTo: 1
                lowStepSize: 0.1
                highFrom: -1
                highTo: 1
                highStepSize: 0.1

                onLowChanged:
                {
                    implementation.setPanScaleLow(low)
                }
                onHighChanged:
                {
                    implementation.setPanScaleHigh(high)
                }
                onExponentChanged:
                {
                    implementation.setPanScaleExponent(exponent)
                }
                onScaledChanged:
                {
                    implementation.setPanScaled(scaled)
                }
            }
        }
    }
}
