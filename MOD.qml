import QtQuick 2.7
import SonLib 1.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0
import "Style.js" as Style

SynthItem {
    id: root
    label: qsTr("MOD")
    type: QtSynthGraph.MODULATOR
    mainColor: Style.modColor
    textColor: Style.itemTextColor

    Component.onCompleted: {

    }

    Editor {

        id: editor
        property int waveform: QtSynthItem.SINE
        property  int  modType: QtSynthItem.AMOD
        property bool useFixedFreq: true
        property double fixedFreq: 1
        property bool useFreqScaling: true
        property double freqScaleLow: 40
        property double freqScaleHigh: 16000
        property double freqScaleExp: 1
        property double depth: 100

        Component.onCompleted: {
            waveformEditor.comboBox.currentIndex = waveform
            frequencyEditor.spinBox.value = fixedFreq * 100
            fixedEditor.checkBox.checked = useFixedFreq
            frequencyScaler.lowSpinBox.value = freqScaleLow * 100
            frequencyScaler.highSpinBox.value = freqScaleHigh * 100
            frequencyScaler.expSpinBox.value = freqScaleExp * 100
            frequencyScaler.checkBox.checked = useFreqScaling
            modEditor.spinBox.value = depth * 100
            modEditor.comboBox.currentIndex = modType
        }

        onWaveformChanged: {
            implementation.setWaveform(waveform)
        }

        onUseFixedFreqChanged: {
            implementation.setUseFixedFreq(useFixedFreq)
        }

        onFixedFreqChanged: {
            implementation.setFixedFreq(fixedFreq)
        }

        onModTypeChanged: {
            implementation.setModType(modType)
        }

        onDepthChanged: {
            implementation.setDepth(depth)
        }

        EditorLayout {
            id: layout
            title: label

            EditorWaveform {
                id: waveformEditor
                onWaveformChanged: {
                    if (editor.waveform != form) {
                        editor.waveform = form
                    }
                }
            }

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
                onMappingsChanged:
                {
                    if(root.mappedRows !== mappings) {
                        root.mappedRows = mappings
                        var implementationMappings = mappings.map( function(value) {
                            return value - 1;
                        } )
                        implementation.setIndexes(implementationMappings)
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
                        implementation.setFreqScalingVals(editor.freqScaleLow,
                                                          editor.freqScaleHigh,
                                                          editor.freqScaleExp)
                    }
                }
                onHighChanged:
                {
                    if(editor.freqScaleHigh !== high) {
                        editor.freqScaleHigh = high
                        implementation.setFreqScalingVals(editor.freqScaleLow,
                                                          editor.freqScaleHigh,
                                                          editor.freqScaleExp)                    }
                }
                onExponentChanged:
                {
                    if(editor.freqScaleExp !== exp) {
                        editor.freqScaleExp = exp
                        implementation.setFreqScalingVals(editor.freqScaleLow,
                                                          editor.freqScaleHigh,
                                                          editor.freqScaleExp)                    }
                }
                onUseScalingChanged:
                {
                    if(editor.useFreqScaling !== scaling) {
                        editor.useFreqScaling = scaling
                        implementation.setUseFreqScaling(editor.useFreqScaling)
                    }
                }
            }

            EditorModulation {
                id: modEditor
                onModulationChanged: {
                    if(editor.modType !== modulation) {
                        editor.modType = modulation
                    }
                }
                onDepthValueChanged:  {
                    if(editor.depth !== depthValue) {
                        editor.depth = depthValue
                    }
                }
            }
        }
    }

}


