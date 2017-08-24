import QtQuick 2.7
import SonLib 1.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0
import "Style.js" as Style

SynthItem {
    id: root
    label: qsTr("MOD")
    type: QtTransport.MODULATOR
    mainColor: Style.modColor
    textColor: Style.itemTextColor

    Component.onCompleted: {
        create()
        frequencyEditor.value = implementation.getFreq()
        fixedFreqEditor.fixed = implementation.getFreqFixed()
        frequencyScaler.low = implementation.getFreqScaleLow()
        frequencyScaler.high = implementation.getFreqScaleHigh()
        frequencyScaler.exponent = implementation.getFreqScaleExponent()
        frequencyScaler.scaled = implementation.getFreqScaled()
        modEditor.depth = implementation.getDepth()
        modEditor.setModType(implementation.getModType())
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
            "modType": implementation.getModType(),
            "freqIndexes": freqIndexesArray,
            "depthIndexes": depthIndexesArray,
            "parents": parents,
            "useFixedFreq": implementation.getFreqFixed(),
            "freq": implementation.getFreq(),
            "useFreqScaling": implementation.getFreqScaled(),
            "freqScaleLow": implementation.getFreqScaleLow(),
            "freqScaleHigh": implementation.getFreqScaleHigh(),
            "freqScaleExp": implementation.getFreqScaleExponent(),
            "useFixedDepth": implementation.getFreqFixed(),
            "depth": implementation.getFreq(),
            "useDepthScaling": implementation.getFreqScaled(),
            "depthScaleLow": implementation.getFreqScaleLow(),
            "depthScaleHigh": implementation.getFreqScaleHigh(),
            "depthScaleExp": implementation.getFreqScaleExponent()
        }
        return essence
    }

    // initialize self from json
    function init(essence) {
        x = essence["x"]
        y = essence["y"]
        identifier = essence["identifier"]
        muted = essence["muted"]
        modEditor.setModType(essence["modType"])
        frequencyEditor.value = essence["freq"]
        fixedFrequencyEditor.fixed = essence["useFixedFreq"]
        var indexes = essence["freqIndexes"]
        var stringIndexes = SessionCode.indexesToString(indexes)
        frequencyMapper.text = stringIndexes
        frequencyMapper.validateMappings()
        frequencyScaler.low = essence["freqScaleLow"]
        frequencyScaler.high = essence["freqScaleHigh"]
        frequencyScaler.exponent = essence["freqScaleExp"]
        frequencyScaler.scaled = essence["useFreqScaling"]
        indexes = essence["depthIndexes"]
        stringIndexes = SessionCode.indexesToString(indexes)
        depthMapper.text = stringIndexes
        depthMapper.validateMappings()
        depthScaler.low = essence["freqScaleLow"]
        depthScaler.high = essence["freqScaleHigh"]
        depthScaler.exponent = essence["freqScaleExp"]
        depthScaler.scaled = essence["useFreqScaling"]
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
                    id: fixedFreqEditor
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
                    if(root.mappedRows !== mappings) {
                        root.mappedRows = mappings
                        var implementationMappings = mappings.map( function(value) {
                            return value - 1;
                        } )
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

                    var mod
                    switch(modulation) {
                    case 0:
                        mod = QtSynthItem.AMPLITUDE
                        break
                    case 1:
                        mod = QtSynthItem.FREQUENCY
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
                    implementation.setModType(mod)
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
                        if(root.mappedRowsDepth !== mappings) {
                            root.mappedRowsDepth = mappings
                            var implementationMappings = mappings.map( function(value) {
                                return value - 1;
                            } )
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
                    if(implementation !== null) {
                        implementation.setDepthScaleLow(low)
                    }
                }
                onHighChanged:
                {
                    if(implementation !== null) {
                        implementation.setDepthScaleHigh(high)
                    }
                }
                onExponentChanged:
                {
                    if(implementation !== null) {
                        implementation.setDepthScaleExponent(exponent)
                    }
                }
                onScaledChanged:
                {
                    if(implementation !== null) {
                        implementation.setDepthScaled(scaled)
                    }
                }
            }
        }
    }

}


