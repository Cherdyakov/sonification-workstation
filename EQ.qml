import QtQuick 2.7
import SonLib 1.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0
import "Style.js" as Style

SynthItem {
    id: root
    label: qsTr("EQ")
    type: QtTransport.EQUALIZER
    childType: QtSynthItem.INPUT
    mainColor: Style.eqColor
    textColor: Style.itemTextColor

    property var mappedRowsResonance: []

    Editor {

        id: editor
        property int filterType: QtSynthItem.LOW_PASS
        property bool useFixedFreq: true
        property double fixedFreq: 1000
        property bool useFreqScaling: true
        property double freqScaleLow: 40
        property double freqScaleHigh: 16000
        property double freqScaleExp: 1
        property double resonance: 100
        property  bool useFixedResonance: true
        property double resonanceScaleLow: 40
        property double resonanceScaleHigh:16000
        property double resonanceScaleExp:1
        property  bool useResonanceScaling: true

        Component.onCompleted: {
            frequencyEditor.spinBox.value = fixedFreq * 100
            fixedFreqEditor.checkBox.checked = useFixedFreq
            frequencyScaler.lowSpinBox.value = freqScaleLow * 100
            frequencyScaler.highSpinBox.value = freqScaleHigh * 100
            frequencyScaler.expSpinBox.value = freqScaleExp * 100
            frequencyScaler.checkBox.checked = useFreqScaling
            resonanceEditor.spinBox.value = resonance * 100
            resonanceScaler.checkBox.checked = useResonanceScaling
            resonanceScaler.lowSpinBox.value = resonanceScaleLow * 100
            fixedResonanceEditor.checkBox.checked = useFixedResonance
            resonanceScaler.highSpinBox.value = resonanceScaleHigh * 100
            resonanceScaler.expSpinBox.value = resonanceScaleExp * 100
        }

        onUseFixedFreqChanged: {
            implementation.setFrequencyFixed(useFixedFreq)
        }

        onFixedFreqChanged: {
            implementation.setFrequency(fixedFreq)
        }

        onFilterTypeChanged: {
            implementation.setFilterType(filterType)
        }

        onResonanceChanged: {
            implementation.setResonance(resonance)
        }

        onUseFixedResonanceChanged: {
            implementation.setResonanceFixed(useFixedResonance)
        }

        EditorLayout {
            id: layout
            title: label

            RowLayout {

                EditorMenuParam {
                    id: typeEditor
                    label.text: qsTr("Type: ")
                    model: [qsTr("Low Pass"), qsTr("High Pass"), qsTr("Peak"), qsTr("Notch")]
                    onValueChanged: {
                        if(editor.filterType !== value) {
                            editor.filterType = value
                        }
                    }
                }

                EditorDoubleParam {
                    id: frequencyEditor
                    label.text: qsTr("Frequency: ")
                    onParamValueChanged: {
                        if (editor.fixedFreq !== value) {
                            editor.fixedFreq = value
                        }
                    }
                }

                EditorFixedParam {
                    id: fixedFreqEditor
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
                maxIndexes: 1
                onMappingsChanged:
                {
                    if(root.mappedRows !== mappings) {
                        root.mappedRows = mappings
                        var implementationMappings = mappings.map( function(value) {
                            return value - 1;
                        } )
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
                    if(editor.freqScaleLow !== low) {
                        editor.freqScaleLow = low
                        implementation.setFrequencyScaleVals(editor.freqScaleLow,
                                                        editor.freqScaleHigh,
                                                        editor.freqScaleExp)
                    }
                }
                onHighChanged:
                {
                    if(editor.freqScaleHigh !== high) {
                        editor.freqScaleHigh = high
                        implementation.setFrequencyScaleVals(editor.freqScaleLow,
                                                        editor.freqScaleHigh,
                                                        editor.freqScaleExp)                    }
                }
                onExponentChanged:
                {
                    if(editor.freqScaleExp !== exp) {
                        editor.freqScaleExp = exp
                        implementation.setFrequencyScaleVals(editor.freqScaleLow,
                                                        editor.freqScaleHigh,
                                                        editor.freqScaleExp)                    }
                }
                onUseScalingChanged:
                {
                    if(editor.useFreqScaling !== scaling) {
                        editor.useFreqScaling = scaling
                        implementation.setFrequencyScaled(editor.useFreqScaling)
                    }
                }
            }


            EditorDoubleParam {
                id: resonanceEditor
                label.text: "Resonance: "
                onParamValueChanged: {
                    if(editor.resonance !== value) {
                        editor.resonance = value
                    }
                }
            }

            RowLayout {

                EditorMapper {
                    id: resonanceMapper
                    label.text: qsTr("Resonance Source: ")
                    maxIndexes: 1
                    onMappingsChanged:
                    {
                        if(root.mappedRowsResonance !== mappings) {
                            root.mappedRowsResonance = mappings
                            var implementationMappings = mappings.map( function(value) {
                                return value - 1;
                            } )
                            implementation.setResonanceIndexes(implementationMappings)
                        }
                    }
                }

                EditorFixedParam {
                    id: fixedResonanceEditor
                    label.text: qsTr("Fixed: ")
                    onFixedChanged: {
                        if (editor.useFixedResonance != fixed) {
                            editor.useFixedResonance = fixed
                        }
                    }
                }
            }

            EditorScaler {
                id: resonanceScaler
                label.text: qsTr("Resonance Scaling: ")
                lowLabel.text: qsTr("Resonance Low: ")
                highLabel.text: qsTr("Resonance High: ")

                onLowChanged:
                {
                    if(editor.resonanceScaleLow !== low) {
                        editor.resonanceScaleLow = low
                        implementation.setResonanceScaleVals(editor.resonanceScaleLow,
                                                         editor.resonanceScaleHigh,
                                                         editor.resonanceScaleExp)
                    }
                }
                onHighChanged:
                {
                    if(editor.resonanceScaleHigh !== high) {
                        editor.resonanceScaleHigh = high
                        implementation.setResonanceScaleVals(editor.resonanceScaleLow,
                                                         editor.resonanceScaleHigh,
                                                         editor.resonanceScaleExp)                    }
                }
                onExponentChanged:
                {
                    if(editor.resonanceScaleExp !== exp) {
                        editor.resonanceScaleExp = exp
                        implementation.setResonanceScaleVals(editor.resonanceScaleLow,
                                                         editor.resonanceScaleHigh,
                                                         editor.resonanceScaleExp)                    }
                }
                onUseScalingChanged:
                {
                    if(editor.useResonanceScaling !== scaling) {
                        editor.useResonanceScaling = scaling
                        implementation.setResonanceScaled(editor.useResonanceScaling)
                    }
                }
            }
        }
    }

}


