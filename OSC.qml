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
        frequencyEditor.spinBox.value = essence["freq"]
        fixedFrequencyEditor.checkBox.checked = essence["useFixedFreq"]
        var indexes = essence["freqIndexes"]
        var stringIndexes = SessionCode.indexesToString(indexes)
        frequencyMapper.textInput.text = stringIndexes
        frequencyMapper.validateMappings()
        frequencyScaler.lowSpinBox.value = essence["freqScaleLow"]
        frequencyScaler.highSpinBox.value = essence["freqScaleHigh"]
        frequencyScaler.expSpinBox.value = essence["freqScaleExp"]
        frequencyScaler.checkBox.checked = essence["useFreqScaling"]
    }

    Editor {

        id: editor

        Component.onCompleted: {
            create()
            frequencyEditor.spinBox.value = implementation.getFreq() * 100
            fixedFrequencyEditor.checkBox.checked = implementation.getFreqFixed()
            frequencyMapper.textInput.text = "1,2,3"
            frequencyMapper.validateMappings()
            frequencyScaler.lowSpinBox.value = implementation.getFreqScaleLow() * 100
            frequencyScaler.highSpinBox.value = implementation.getFreqScaleHigh() * 100
            frequencyScaler.expSpinBox.value = implementation.getFreqScaleExponent * 100
            frequencyScaler.checkBox.checked = implementation.getFreqScaled()
        }

        EditorLayout {
            id: layout
            title: label

            RowLayout {

                EditorDoubleParam {
                    id: frequencyEditor
                    label.text: "Frequency: "
                    onParamValueChanged: {
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
                maxIndexes: 128
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
                    implementation.setFreqScaleLow(low)
                }
                onHighChanged:
                {
                    implementation.setFreqScaleHigh(high)
                }
                onExponentChanged:
                {
                    implementation.setFreqScaleExponent(exp)
                }
                onUseScalingChanged:
                {
                    implementation.setFreqScaled(scaling)
                }
            }
        }
    }
}
