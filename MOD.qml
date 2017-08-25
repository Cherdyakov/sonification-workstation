import QtQuick 2.7
import SonLib 1.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0
import "Style.js" as Style
import "SessionCode.js" as SessionCode

SynthItem {
    id: root
    label: qsTr("MOD")
    type: QtTransport.MODULATOR
    childType: QtSynthItem.AMPLITUDE
    mainColor: Style.modColor
    textColor: Style.itemTextColor

    Component.onCompleted: {
        create()
        frequencyEditor.value = implementation.getFreq()
        fixedFrequencyEditor.fixed = implementation.getFreqFixed()
        frequencyScaler.low = implementation.getFreqScaleLow()
        frequencyScaler.high = implementation.getFreqScaleHigh()
        frequencyScaler.exponent = implementation.getFreqScaleExponent()
        frequencyScaler.scaled = implementation.getFreqScaled()
        modEditor.depth = implementation.getDepth()
        //        modEditor.modFromParameter(1)
        fixedDepthEditor.fixed = implementation.getDepthFixed()
        depthScaler.low = implementation.getDepthScaleLow()
        depthScaler.high = implementation.getDepthScaleHigh()
        depthScaler.exponent = implementation.getDepthScaleExponent()
        depthScaler.scaled = implementation.getDepthScaled()
    }

    // return json representation of self
    function read() {

        var parents = []
        for(var i = 0; i < synthParents.length; i++) {
            var parent = synthParents[i].identifier
            parents.push(parent)
        }

        var freqIndexes = implementation.getFreqIndexes()
        // remove keys from freqIndexes and store in js array
        var freqIndexesArray = Object.keys(freqIndexes).map(function(k) { return freqIndexes[k] });

        var depthIndexes = implementation.getDepthIndexes()
        // remove keys from freqIndexes and store in js array
        var depthIndexesArray = Object.keys(depthIndexes).map(function(k) { return depthIndexes[k] });

        var essence = {
            "identifier": identifier,
            "type": type,
            "x": x,
            "y": y,
            "muted": implementation.getMute(),
            "modType": childType,
            "freqIndexes": freqIndexesArray,
            "depthIndexes": depthIndexesArray,
            "parents": parents,
            "freq": implementation.getFreq(),
            "freqFixed": implementation.getFreqFixed(),
            "freqScaled": implementation.getFreqScaled(),
            "freqScaleLow": implementation.getFreqScaleLow(),
            "freqScaleHigh": implementation.getFreqScaleHigh(),
            "freqScaleExponent": implementation.getFreqScaleExponent(),
            "depth": implementation.getDepth(),
            "depthFixed": implementation.getDepthFixed(),
            "depthScaled": implementation.getDepthScaled(),
            "depthScaleLow": implementation.getDepthScaleLow(),
            "depthScaleHigh": implementation.getDepthScaleHigh(),
            "depthScaleExponent": implementation.getDepthScaleExponent()
        }
        return essence
    }

    // initialize self from json
    function init(essence) {
        x = essence["x"]
        y = essence["y"]
        identifier = essence["identifier"]
        muted = essence["muted"]
        modEditor.modFromParameter(essence["modType"])
        frequencyEditor.value = essence["freq"]
        fixedFrequencyEditor.fixed = essence["useFixedFreq"]
        var indexes = essence["freqIndexes"]
        var stringIndexes = SessionCode.indexesToString(indexes)
        frequencyMapper.text = stringIndexes
        frequencyMapper.validateMappings()
        frequencyScaler.scaled = essence["freqScaled"]
        frequencyScaler.low = essence["freqScaleLow"]
        frequencyScaler.high = essence["freqScaleHigh"]
        frequencyScaler.exponent = essence["freqScaleExponent"]
        indexes = essence["depthIndexes"]
        stringIndexes = SessionCode.indexesToString(indexes)
        depthMapper.text = stringIndexes
        depthMapper.validateMappings()
        depthScaler.scaled = essence["depthScaled"]
        depthScaler.low = essence["depthScaleLow"]
        depthScaler.high = essence["depthScaleHigh"]
        depthScaler.exponent = essence["depthScaleExponent"]
    }


    Editor {

        id: editor

        EditorLayout {
            id: layout
            title: label

            RowLayout {

                EditorDoubleParam {
                    id: frequencyEditor
                    label.text: qsTr("Frequency: ")
                    onValueChanged: {
                        implementation.setFreq(value)
                    }
                }

                EditorFixedParam {
                    id: fixedFrequencyEditor
                    label.text: qsTr("Fixed: ")
                    onFixedChanged: {
                        implementation.setFreqFixed(fixed)
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
                        implementation.setFreqIndexes(implementationMappings)
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

            EditorModulation {
                id: modEditor
                onModulationChanged: {
                    if(implementation === null) {
                        return
                    }
                    switch(modulation) {
                    case "Amplitude":
                        childType = QtSynthItem.AMPLITUDE
                        break
                    case "Frequency":
                        childType = QtSynthItem.FREQUENCY
                        break
                    default:
                        break
                    }

                    var parentsCopy = synthParents.slice();
                    for(var i = 0; i < parentsCopy.length; i++) {
                        var synthItem = parentsCopy[i]
                        synthItem.removeChild(root)
                        removeParent(synthItem)
                    }
                    implementation.setModType(childType)
                    for(i = 0; i < parentsCopy.length; i++) {
                        synthItem = parentsCopy[i]
                        synthItem.addChild(root)
                    }
                }
                onDepthChanged: {
                    implementation.setDepth(depth)
                }
            }

            RowLayout {

                EditorMapper {
                    id: depthMapper
                    label.text: qsTr("Depth Source: ")
                    maxIndexes: 1
                    onMappingsChanged:
                    {
                        var implementationMappings = mappings.map(function(value) {
                            return value - 1
                        } )
                        if(implementation !== null) {
                            implementation.setDepthIndexes(implementationMappings)
                        }
                    }
                }

                EditorFixedParam {
                    id: fixedDepthEditor
                    label.text: qsTr("Fixed: ")
                    onFixedChanged: {
                        implementation.setDepthFixed(fixed)
                    }
                }
            }

            EditorScaler {
                id: depthScaler
                label.text: qsTr("Depth Scaling: ")
                lowLabel.text: qsTr("Depth Low: ")
                highLabel.text: qsTr("Depth High: ")

                onLowChanged:
                {
                    implementation.setDepthScaleLow(low)
                }
                onHighChanged:
                {
                    implementation.setDepthScaleHigh(high)
                }
                onExponentChanged:
                {
                    implementation.setDepthScaleExponent(exponent)
                }
                onScaledChanged:
                {
                    implementation.setDepthScaled(scaled)
                }
            }
        }
    }

}


