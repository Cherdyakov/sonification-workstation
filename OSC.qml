import QtQuick 2.7
import SonLib 1.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0
import "Style.js" as Style
import "SessionCode.js" as SessionCode

SynthItem {
    id: root
    label: qsTr("OSC")
    type: QtTransport.OSCILLATOR
    childType: QtSynthItem.INPUT
    mainColor: Style.oscColor
    textColor: Style.itemTextColor

    function read() {

        var parents = []
        for(var i = 0; i < synthParents.length; i++) {
            var parent = synthParents[i].identifier
            parents.push(parent)
        }

        var freqIndexes = implementation.getFreqIndexes()
        // remove keys from freqIndexes and store in js array
        var freqIndexesArray = Object.keys(freqIndexes).map(function(k) { return freqIndexes[k] });

        var essence = {
            "identifier": identifier,
            "type": type,
            "x": x,
            "y": y,
            "muted": implementation.getMute(),
            "freqIndexes": freqIndexesArray,
            "parents": parents,
            "useFixedFreq": implementation.getFreqFixed(),
            "freq": implementation.getFreq(),
            "useFreqScaling": implementation.getFreqScaled(),
            "freqScaleLow": implementation.getFreqScaleLow(),
            "freqScaleHigh": implementation.getFreqScaleHigh(),
            "freqScaleExp": implementation.getFreqScaleExponent()
        }

        return essence
    }

    function init(essence) {
        x = essence["x"]
        y = essence["y"]
        identifier = essence["identifier"]
        muted = essence["muted"]
        frequencyEditor.value = essence["freq"]
        fixedFrequencyEditor.fixed = essence["useFixedFreq"]
        var indexes = essence["freqIndexes"]
        var stringIndexes = SessionCode.indexesToString(indexes)
        frequencyMapper.textInput.text = stringIndexes
        frequencyMapper.validateMappings()
        frequencyScaler.low = essence["freqScaleLow"]
        frequencyScaler.high = essence["freqScaleHigh"]
        frequencyScaler.exponent = essence["freqScaleExp"]
        frequencyScaler.scaled = essence["useFreqScaling"]
    }

    Editor {

        id: editor

        Component.onCompleted: {
            create()
            frequencyEditor.value = implementation.getFreq()
            fixedFrequencyEditor.fixed = implementation.getFreqFixed()
//            var indexes = implementation.getFreqIndexes();
//            var stringIndexes = SessionCode.indexesToString(indexes)
//            frequencyMapper.textInput.text = stringIndexes
            frequencyMapper.validateMappings()
            frequencyScaler.low = implementation.getFreqScaleLow()
            frequencyScaler.high = implementation.getFreqScaleHigh()
            frequencyScaler.exponent = implementation.getFreqScaleExponent()
            frequencyScaler.scaled = implementation.getFreqScaled()
        }

        EditorLayout {
            id: layout
            title: label

            RowLayout {

                EditorDoubleParam {
                    id: frequencyEditor
                    label.text: "Frequency: "
                    onValueChanged: {
                        if(implementation !== null) {
                            implementation.setFreq(value)
                        }
                    }
                }

                EditorFixedParam {
                    id: fixedFrequencyEditor
                    label.text: qsTr("Fixed: ")
                    onFixedChanged: {
                        if(implementation !== null) {
                            implementation.setFreqFixed(fixed)
                        }
                    }
                }

            }

            EditorMapper {
                id: frequencyMapper
                label.text: qsTr("Frequency Source: ")
                maxIndexes: 128
                onMappingsChanged:
                {
                    if(root.mappedRows !== mappings) {
                        root.mappedRows = mappings
                        var implementationMappings = mappings.map( function(value) {
                            return value - 1;
                        } )
                        if(implementation !== null) {
                            implementation.setFreqIndexes(implementationMappings)
                        }
                    }
                }
            }

            EditorScaler {
                id: frequencyScaler
                label.text: qsTr("Frequency Scaling: ")
                lowLabel.text: qsTr("Frequency Low: ")
                highLabel.text: qsTr("Frequency High: ")

                onLowChanged:
                {
                    if(implementation !== null) {
                        implementation.setFreqScaleLow(low)
                    }
                }
                onHighChanged:
                {
                    if(implementation !== null) {
                        implementation.setFreqScaleHigh(high)
                    }
                }
                onExponentChanged:
                {
                    if(implementation !== null) {
                        implementation.setFreqScaleExponent(exponent)
                    }
                }
                onScaledChanged:
                {
                    if(implementation !== null) {
                        implementation.setFreqScaled(scaled)
                    }
                }
            }
        }
    }
}
