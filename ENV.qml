//import QtQuick 2.7
//import SonLib 1.0
//import QtQuick.Layouts 1.1
//import QtQuick.Controls 2.0
//import "Style.js" as Style

//SynthItem {
//    id: root
//    label: qsTr("ENV")
//    type: QtTransport.ENVELOPE
//    childType: QtSynthItem.INPUT
//    mainColor: Style.envColor
//    textColor: Style.itemTextColor

//    Editor {

//        id: editor
//        property bool useFixedAtt: true
//        property double fixedAtt: 0.5
//        property bool useAttScaling: true
//        property double attScaleLow: 40
//        property double attScaleHigh:6000
//        property double attScaleExp: 1

//        Component.onCompleted: {
//            attackEditor.spinBox.value = fixedFreq * 100
//            fixedEditor.checkBox.checked = useFixedFreq
//            attackScaler.lowSpinBox.value = freqScaleLow * 100
//            attackScaler.highSpinBox.value = freqScaleHigh * 100
//            attackScaler.expSpinBox.value = freqScaleExp * 100
//            attackScaler.checkBox.checked = useFreqScaling
//        }

//        onUseFixedFreqChanged: {
//            implementation.setFreqFixed(useFixedFreq)
//        }

//        onFixedFreqChanged: {
//            implementation.setFreq(fixedFreq)
//        }

//        EditorLayout {
//            id: layout
//            title: label

//            RowLayout {

//                EditorAttack {
//                    id: frequencyEditor
//                    onAttackChanged: {
//                        if (editor.fixedFreq !== freq) {
//                            editor.fixedFreq = freq
//                        }
//                    }
//                }

//                EditorFixedParam {
//                    id: fixedEditor
//                    label.text: qsTr("Fixed: ")
//                    onFixedChanged: {
//                        if (editor.useFixedFreq != fixed) {
//                            editor.useFixedFreq = fixed
//                        }
//                    }
//                }

//            }

//            EditorMapper {
//                id: frequencyMapper
//                label.text: qsTr("Frequency Source: ")
//                maxIndexes: 128
//                onMappingsChanged:
//                {
//                    if(root.mappedRows !== mappings) {
//                        root.mappedRows = mappings
//                        var implementationMappings = mappings.map( function(value) {
//                            return value - 1;
//                        } )
//                        implementation.setFreqIndexes(implementationMappings)
//                    }
//                }
//            }

//            EditorScaler {
//                id: frequencyScaler
//                label.text: qsTr("Frequency Scaling: ")
//                lowLabel.text: qsTr("Frequency Low: ")
//                highLabel.text: qsTr("Frequency High: ")

//                onLowChanged:
//                {
//                    if(editor.freqScaleLow !== low) {
//                        editor.freqScaleLow = low
//                        implementation.setFreqScaleVals(editor.freqScaleLow,
//                                                          editor.freqScaleHigh,
//                                                          editor.freqScaleExp)
//                    }
//                }
//                onHighChanged:
//                {
//                    if(editor.freqScaleHigh !== high) {
//                        editor.freqScaleHigh = high
//                        implementation.setFreqScaleVals(editor.freqScaleLow,
//                                                          editor.freqScaleHigh,
//                                                          editor.freqScaleExp)                    }
//                }
//                onExponentChanged:
//                {
//                    if(editor.freqScaleExp !== exp) {
//                        editor.freqScaleExp = exp
//                        implementation.setFreqScaleVals(editor.freqScaleLow,
//                                                          editor.freqScaleHigh,
//                                                          editor.freqScaleExp)                    }
//                }
//                onUseScalingChanged:
//                {
//                    if(editor.useFreqScaling !== scaling) {
//                        editor.useFreqScaling = scaling
//                        implementation.setFreqScaled(editor.useFreqScaling)
//                    }
//                }
//            }
//        }
//    }

//}
