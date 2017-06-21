import QtQuick 2.7
import SonLib 1.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0
import "Style.js" as Style

SynthItem {
    id: root
    label: qsTr("ENV")
    type: QtTransport.ENVELOPE
    childType: QtSynthItem.INPUT
    mainColor: Style.envColor
    textColor: Style.itemTextColor

    Editor {

        id: editor
        property bool useFixedAttack: true
        property double fixedAttack: 0.5
        property bool useAttackScaling: true
        property double attackScaleLow: 40
        property double attackScaleHigh:6000
        property double attackScaleExp: 1

        property bool useFixedDecay: true
        property double fixedDecay: 0.5
        property bool useDecayScaling: true
        property double decayScaleLow: 40
        property double decayScaleHigh:6000
        property double decayScaleExp: 1

        Component.onCompleted: {
            attackEditor.spinBox.value = fixedAttack * 100
            attackFixedEditor.checkBox.checked = useFixedAttack
            attackScaler.lowSpinBox.value = attackScaleLow * 100
            attackScaler.highSpinBox.value = attackScaleHigh * 100
            attackScaler.expSpinBox.value = attackScaleExp * 100
            attackScaler.checkBox.checked = useAttackScaling

            decayEditor.spinBox.value = fixedDecay * 100
            decayFixedEditor.checkBox.checked = useFixedDecay
            decayScaler.lowSpinBox.value = decayScaleLow * 100
            decayScaler.highSpinBox.value = decayScaleHigh * 100
            decayScaler.expSpinBox.value = decayScaleExp * 100
            decayScaler.checkBox.checked = useDecayScaling
        }

        onUseFixedAttackChanged: {
            implementation.setAttackFixed(useFixedAttack)
        }

        onFixedAttackChanged: {
            implementation.setAttack(fixedAttack)
        }

        EditorLayout {
            id: layout
            title: label

            //
            // ATTACK PARAMETER
            //
            RowLayout {

                EditorDoubleParam {
                    id: attackEditor
                    label.text: "Attack: "
                    onParamValueChanged: {
                        if (editor.fixedAttack !== value) {
                            editor.fixedAttack = value
                        }
                    }
                }

                EditorFixedParam {
                    id: attackFixedEditor
                    label.text: qsTr("Fixed: ")
                    onFixedChanged: {
                        if (editor.useFixedAttack !== fixed) {
                            editor.useFixedAttack = fixed
                        }
                    }
                }

            }

            EditorMapper {
                id: attackMapper
                label.text: qsTr("Attack Source: ")
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
                id: attackScaler
                label.text: qsTr("Attack Scaling: ")
                lowLabel.text: qsTr("Attack Low: ")
                highLabel.text: qsTr("Attack High: ")

                onLowChanged:
                {
                    if(editor.attackScaleLow !== low) {
                        editor.attackScaleLow = low
                        implementation.setAttackScaleVals(editor.attScaleLow,
                                                          editor.attackScaleHigh,
                                                          editor.attackScaleExp)
                    }
                }
                onHighChanged:
                {
                    if(editor.attackScaleHigh !== high) {
                        editor.attackScaleHigh = high
                        implementation.setAttackScaleVals(editor.attackScaleLow,
                                                          editor.attackScaleHigh,
                                                          editor.attackScaleExp)                    }
                }
                onExponentChanged:
                {
                    if(editor.attackScaleExp !== exp) {
                        editor.attackScaleExp = exp
                        implementation.setAttackScaleVals(editor.attackScaleLow,
                                                          editor.attackScaleHigh,
                                                          editor.attackScaleExp)                    }
                }
                onUseScalingChanged:
                {
                    if(editor.useAttackScaling !== scaling) {
                        editor.useAttackScaling = scaling
                        implementation.setAttackScaled(editor.useAttackScaling)
                    }
                }
            }

            //
            // DECAY PARAMETER
            //
            RowLayout {

                EditorDoubleParam {
                    id: decayEditor
                    label.text: "Decay: "
                    onParamValueChanged: {
                        if (editor.fixedDecay !== value) {
                            editor.fixedDecay = value
                        }
                    }
                }

                EditorFixedParam {
                    id: decayFixedEditor
                    label.text: qsTr("Fixed: ")
                    onFixedChanged: {
                        if (editor.useFixedDecay !== fixed) {
                            editor.useFixedDecay = fixed
                        }
                    }
                }

            }

            EditorMapper {
                id: decayMapper
                label.text: qsTr("Decay Source: ")
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
                id: decayScaler
                label.text: qsTr("Decay Scaling: ")
                lowLabel.text: qsTr("Decay Low: ")
                highLabel.text: qsTr("Decay High: ")

                onLowChanged:
                {
                    if(editor.decayScaleLow !== low) {
                        editor.decayScaleLow = low
                        implementation.setDecayScaleVals(editor.attScaleLow,
                                                          editor.decayScaleHigh,
                                                          editor.decayScaleExp)
                    }
                }
                onHighChanged:
                {
                    if(editor.decayScaleHigh !== high) {
                        editor.decayScaleHigh = high
                        implementation.setDecayScaleVals(editor.decayScaleLow,
                                                          editor.decayScaleHigh,
                                                          editor.decayScaleExp)                    }
                }
                onExponentChanged:
                {
                    if(editor.decayScaleExp !== exp) {
                        editor.decayScaleExp = exp
                        implementation.setDecayScaleVals(editor.decayScaleLow,
                                                          editor.decayScaleHigh,
                                                          editor.decayScaleExp)                    }
                }
                onUseScalingChanged:
                {
                    if(editor.useDecayScaling !== scaling) {
                        editor.useDecayScaling = scaling
                        implementation.setDecayScaled(editor.useDecayScaling)
                    }
                }
            }
        }
    }

}
