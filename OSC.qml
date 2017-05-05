import QtQuick 2.7
import SonLib 1.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0
import "Style.js" as Style

SynthItem {
    id: root
    label: qsTr("OSC")
    type: QtTransport.OSCILLATOR
    childType: QtSynthItem.INPUT
    mainColor: Style.oscColor
    textColor: Style.itemTextColor

    Editor {

        id: editor
        property bool useFixedFreq: true
        property double fixedFreq: 440
        property bool useFreqScaling: true
        property double freqScaleLow: 40
        property double freqScaleHigh: 16000
        property double freqScaleExp: 1

        Component.onCompleted: {
            frequencyEditor.spinBox.value = fixedFreq * 100
            fixedEditor.checkBox.checked = useFixedFreq
            frequencyScaler.lowSpinBox.value = freqScaleLow * 100
            frequencyScaler.highSpinBox.value = freqScaleHigh * 100
            frequencyScaler.expSpinBox.value = freqScaleExp * 100
            frequencyScaler.checkBox.checked = useFreqScaling
        }

        onUseFixedFreqChanged: {
            implementation.setFreqFixed(useFixedFreq)
        }

        onFixedFreqChanged: {
            implementation.setFreq(fixedFreq)
        }

        EditorLayout {
            id: layout
            title: label

            RowLayout {

                EditorFrequency {
                    id: frequencyEditor
                    onFrequencyChanged: {
                        if (editor.fixedFreq !== freq) {
                            editor.fixedFreq = freq
                        }
                    }
                }

                EditorFixedParam {
                    id: fixedEditor
                    label.text: qsTr("Fixed: ")
                    onFixedChanged: {
                        if (editor.useFixedFreq != fixed) {
                            editor.useFixedFreq = fixed
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
                    if(editor.freqScaleLow !== low) {
                        editor.freqScaleLow = low
                        implementation.setFreqScaleVals(editor.freqScaleLow,
                                                          editor.freqScaleHigh,
                                                          editor.freqScaleExp)
                    }
                }
                onHighChanged:
                {
                    if(editor.freqScaleHigh !== high) {
                        editor.freqScaleHigh = high
                        implementation.setFreqScaleVals(editor.freqScaleLow,
                                                          editor.freqScaleHigh,
                                                          editor.freqScaleExp)                    }
                }
                onExponentChanged:
                {
                    if(editor.freqScaleExp !== exp) {
                        editor.freqScaleExp = exp
                        implementation.setFreqScaleVals(editor.freqScaleLow,
                                                          editor.freqScaleHigh,
                                                          editor.freqScaleExp)                    }
                }
                onUseScalingChanged:
                {
                    if(editor.useFreqScaling !== scaling) {
                        editor.useFreqScaling = scaling
                        implementation.setFreqScaled(editor.useFreqScaling)
                    }
                }
            }
        }
    }

}


