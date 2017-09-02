import QtQuick 2.7
import SonLib 1.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0
import "Style.js" as Style
import "SessionCode.js" as SessionCode

SynthItem {
    id: root
    label: qsTr("EQ")
    type: QtTransport.EQUALIZER
    childType: QtSynthItem.INPUT
    mainColor: Style.eqColor
    textColor: Style.itemTextColor

    Component.onCompleted: {
        create()
        frequencyEditor.value = implementation.getFrequency()
        fixedFrequencyEditor.fixed = implementation.getFrequencyFixed()
        frequencyScaler.scaled = implementation.getFrequencyScaled()
        frequencyScaler.low = implementation.getFrequencyScaleLow()
        frequencyScaler.high = implementation.getFrequencyScaleHigh()
        frequencyScaler.exponent = implementation.getFrequencyScaleExponent()
        resonanceEditor.value = implementation.getResonance()
        fixedResonanceEditor.fixed = implementation.getResonanceFixed()
        resonanceScaler.scaled = implementation.getResonanceScaled()
        resonanceScaler.low = implementation.getResonanceScaleLow()
        resonanceScaler.high = implementation.getResonanceScaleHigh()
        resonanceScaler.exponent = implementation.getResonanceScaleExponent()
    }

    // return json representation of self
    function read() {

        var parents = []
        for(var i = 0; i < synthParents.length; i++) {
            var parent = synthParents[i].identifier
            parents.push(parent)
        }

        var frequencyIndexes = implementation.getFrequencyIndexes()
        // remove keys from freqIndexes and store in js array
        var frequencyIndexesArray = Object.keys(frequencyIndexes).map(function(k) { return frequencyIndexes[k] });

        var resonanceIndexes = implementation.getResonanceIndexes()
        // remove keys from freqIndexes and store in js array
        var resonanceIndexesArray = Object.keys(resonanceIndexes).map(function(k) { return resonanceIndexes[k] });

        var essence = {
            "identifier": identifier,
            "type": type,
            "x": x,
            "y": y,
            "muted": implementation.getMute(),
            "modType": childType,
            "frequencyIndexes": frequencyIndexesArray,
            "resonanceIndexes": resonanceIndexesArray,
            "parents": parents,
            "frequency": implementation.getFrequency(),
            "frequencyFixed": implementation.getFrequencyFixed(),
            "frequencyScaled": implementation.getFrequencyScaled(),
            "frequencyScaleLow": implementation.getFrequencyScaleLow(),
            "frequencyScaleHigh": implementation.getFrequencyScaleHigh(),
            "frequencyScaleExponent": implementation.getFrequencyScaleExponent(),
            "resonance": implementation.getResonance(),
            "resonanceFixed": implementation.getResonanceFixed(),
            "resonanceScaled": implementation.getResonanceScaled(),
            "resonanceScaleLow": implementation.getResonanceScaleLow(),
            "resonanceScaleHigh": implementation.getResonanceScaleHigh(),
            "resonanceScaleExponent": implementation.getResonanceScaleExponent()
        }
        return essence
    }

    // initialize self from json
    function init(essence) {
        x = essence["x"]
        y = essence["y"]
        identifier = essence["identifier"]
        muted = essence["muted"]
        frequencyEditor.value = essence["frequency"]
        fixedFrequencyEditor.fixed = essence["frequencyFixed"]
        var indexes = essence["frequencyIndexes"]
        var stringIndexes = SessionCode.indexesToString(indexes)
        frequencyMapper.text = stringIndexes
        frequencyMapper.validateMappings()
        frequencyScaler.scaled = essence["frequencyScaled"]
        frequencyScaler.low = essence["frequencyScaleLow"]
        frequencyScaler.high = essence["frequencyScaleHigh"]
        frequencyScaler.exponent = essence["frequencyScaleExponent"]
        resonanceEditor.value = essence["resonance"]
        fixedResonanceEditor.fixed = essence["resonanceFixed"]
        indexes = essence["resonanceIndexes"]
        stringIndexes = SessionCode.indexesToString(indexes)
        resonanceMapper.text = stringIndexes
        resonanceMapper.validateMappings()
        resonanceScaler.scaled = essence["resonanceScaled"]
        resonanceScaler.low = essence["resonanceScaleLow"]
        resonanceScaler.high = essence["resonanceScaleHigh"]
        resonanceScaler.exponent = essence["resonanceScaleExponent"]
    }

    Editor {

        id: editor

        EditorLayout {
            id: layout
            title: label

            EditorMenuParam {
                id: typeEditor
                label.text: qsTr("Type: ")
                model: [qsTr("Low Pass"), qsTr("High Pass"), qsTr("Peak"), qsTr("Notch")]
                onIndexChanged: {
                    if(implementation !== null) {
                        implementation.setFilterType(index)
                    }
                }
            }

            RowLayout {

                EditorDoubleParam {
                    id: frequencyEditor
                    label.text: qsTr("Frequency: ")
                    onValueChanged: {
                        implementation.setFrequency(value)
                    }
                }

                EditorFixedParam {
                    id: fixedFrequencyEditor
                    label.text: qsTr("Fixed: ")
                    onFixedChanged: {
                        implementation.setFrequencyFixed(fixed)
                    }
                }

            }

            EditorMapper {
                id: frequencyMapper
                label.text: qsTr("Frequency Source: ")
                maxIndexes: 1
                onMappingsChanged:
                {
                    var implementationMappings = mappings.map(function(value) {
                        return value - 1
                    } )
                    if(implementation !== null) {
                        implementation.setFrequencyIndexes(implementationMappings)
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
                    implementation.setFrequencyScaleLow(low)
                }
                onHighChanged:
                {
                    implementation.setFrequencyScaleHigh(high)
                }
                onExponentChanged:
                {
                    implementation.setFrequencyScaleExponent(exponent)
                }
                onScaledChanged:
                {
                    implementation.setFrequencyScaled(scaled)
                }
            }


            EditorDoubleParam {
                id: resonanceEditor
                label.text: "Resonance: "
                from: 1
                to: 10
                stepSize: 0.1
                onValueChanged: {
                    implementation.setResonance(value)
                }
            }

            RowLayout {

                EditorMapper {
                    id: resonanceMapper
                    label.text: qsTr("Resonance Source: ")
                    maxIndexes: 1
                    onMappingsChanged:
                    {
                        var implementationMappings = mappings.map(function(value) {
                            return value - 1
                        } )
                        if(implementation !== null) {
                            implementation.setResonanceIndexes(implementationMappings)
                        }
                    }
                }

                EditorFixedParam {
                    id: fixedResonanceEditor
                    label.text: qsTr("Fixed: ")
                    onFixedChanged: {
                        implementation.setResonanceFixed(fixed)
                    }
                }
            }

            EditorScaler {
                id: resonanceScaler
                label.text: qsTr("Resonance Scaling: ")
                lowLabel.text: qsTr("Resonance Low: ")
                highLabel.text: qsTr("Resonance High: ")
                lowFrom: 1
                lowTo: 10
                lowStepSize: 0.1
                highFrom: 1
                highTo: 10
                highStepSize: 0.1

                onLowChanged:
                {
                    implementation.setResonanceScaleLow(low)
                }
                onHighChanged:
                {
                    implementation.setResonanceScaleHigh(high)
                }
                onExponentChanged:
                {
                    implementation.setResonanceScaleExponent(exponent)
                }
                onScaledChanged:
                {
                    implementation.setResonanceScaled(scaled)
                }
            }
        }
    }

}


