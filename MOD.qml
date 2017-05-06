import QtQuick 2.7
import SonLib 1.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0
import "Style.js" as Style

SynthItem {
    id: root
    label: qsTr("MOD")
    type: QtTransport.MODULATOR
    childType: QtSynthItem.AMPLITUDE
    mainColor: Style.modColor
    textColor: Style.itemTextColor


    property var mappedRowsDepth: []

    Component.onCompleted: {

    }

    Editor {

        id: editor
        property  int  modType: QtSynthItem.AMPLITUDE
        property bool useFixedFreq: true
        property double fixedFreq: 1
        property bool useFreqScaling: true
        property double freqScaleLow: 40
        property double freqScaleHigh: 16000
        property double freqScaleExp: 1
        property double depth: 100
        property  bool useFixedDepth: true
        property double depthScaleLow: 40
        property double depthScaleHigh:16000
        property double depthScaleExp:1
        property  bool useDepthScaling: true

        Component.onCompleted: {
            frequencyEditor.spinBox.value = fixedFreq * 100
            fixedFreqEditor.checkBox.checked = useFixedFreq
            frequencyScaler.lowSpinBox.value = freqScaleLow * 100
            frequencyScaler.highSpinBox.value = freqScaleHigh * 100
            frequencyScaler.expSpinBox.value = freqScaleExp * 100
            frequencyScaler.checkBox.checked = useFreqScaling
            modEditor.spinBox.value = depth * 100
            modEditor.comboBox.currentIndex = 0
            depthScaler.checkBox.checked = useDepthScaling
            depthScaler.lowSpinBox.value = depthScaleLow * 100
            fixedDepthEditor.checkBox.checked = useFixedDepth
            depthScaler.highSpinBox.value = depthScaleHigh * 100
            depthScaler.expSpinBox.value = depthScaleExp * 100
        }

        onUseFixedFreqChanged: {
            implementation.setFreqFixed(useFixedFreq)
        }

        onFixedFreqChanged: {
            implementation.setFreq(fixedFreq)
        }

        onModTypeChanged: {
            root.childType = modType           
            var parentsCopy = synthParents.slice();
            for(var i = 0; i < parentsCopy.length; i++) {
                var synthItem = parentsCopy[i]
                synthItem.removeChild(root)
                removeParent(synthItem)
            }
            implementation.setModType(root.childType)
            for(i = 0; i < parentsCopy.length; i++) {
                synthItem = parentsCopy[i]
                synthItem.addChild(root)
            }
        }

        onDepthChanged: {
            implementation.setDepth(depth)
        }

        onUseFixedDepthChanged: {
            implementation.setDepthFixed(useFixedDepth)
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


            EditorModulation {
                id: modEditor
                onModulationChanged: {
                    switch(modulation) {
                    case "Amplitude":
                        editor.modType = QtSynthItem.AMPLITUDE
                        break
                    case "Frequency":
                        editor.modType = QtSynthItem.FREQUENCY
                        break
                    default:
                        break
                    }
                }
                onDepthValueChanged:  {
                    if(editor.depth !== depthValue) {
                        editor.depth = depthValue
                    }
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
                        if (editor.useFixedDepth != fixed) {
                            editor.useFixedDepth = fixed
                        }
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
                    if(editor.depthScaleLow !== low) {
                        editor.depthScaleLow = low
                        implementation.setDepthScaleVals(editor.depthScaleLow,
                                                         editor.depthScaleHigh,
                                                         editor.depthScaleExp)
                    }
                }
                onHighChanged:
                {
                    if(editor.depthScaleHigh !== high) {
                        editor.depthScaleHigh = high
                        implementation.setDepthScaleVals(editor.depthScaleLow,
                                                         editor.depthScaleHigh,
                                                         editor.depthScaleExp)                    }
                }
                onExponentChanged:
                {
                    if(editor.depthScaleExp !== exp) {
                        editor.depthScaleExp = exp
                        implementation.setDepthScaleVals(editor.depthScaleLow,
                                                         editor.depthScaleHigh,
                                                         editor.depthScaleExp)                    }
                }
                onUseScalingChanged:
                {
                    if(editor.useDepthScaling !== scaling) {
                        editor.useDepthScaling = scaling
                        implementation.setDepthScaled(editor.useDepthScaling)
                    }
                }
            }
        }
    }

}


