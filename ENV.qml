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
        property double attack: 0.01
        property bool attackFixed: true
        property bool attackScaled: true
        property double attackLow: 0.1
        property double attackHigh: 1
        property double attackExponent: 1

        property double decay: 0.1
        property bool decayFixed: true
        property bool decayScaled: true
        property double decayLow: 0.1
        property double decayHigh: 1
        property double decayExponent: 1

        Component.onCompleted: {
            attackEditor.spinBox.value = attack * 100
            attackFixedEditor.checkBox.checked = attackFixed
            attackScaler.lowSpinBox.value = attackLow * 100
            attackScaler.highSpinBox.value = attackHigh * 100
            attackScaler.expSpinBox.value = attackExponent * 100
            attackScaler.checkBox.checked = attackScaled

            decayEditor.spinBox.value = decay * 100
            decayFixedEditor.checkBox.checked = decayFixed
            decayScaler.lowSpinBox.value = decayLow * 100
            decayScaler.highSpinBox.value = decayHigh * 100
            decayScaler.expSpinBox.value = decayExponent * 100
            decayScaler.checkBox.checked = decayScaled
        }

        // Update Attack values in implementation
        onAttackChanged: {
            implementation.setAttack(attack)
        }
        onAttackFixedChanged: {
            implementation.setAttackFixed(attackFixed)
        }
        onAttackLowChanged: {
            implementation.setAttackScaleVals(attackLow, attackHigh, attackExponent)
        }
        onAttackHighChanged: {
            implementation.setAttackScaleVals(attackLow, attackHigh, attackExponent)
        }
        onAttackExponentChanged: {
            implementation.setAttackScaleVals(attackLow, attackHigh, attackExponent)
        }
        onAttackScaledChanged: {
            implementation.setAttackScaled(attackScaled)
        }

        // Update Decay values in implemenation
        onDecayChanged: {
            implementation.setDecay(decay)
        }
        onDecayFixedChanged: {
            implementation.setDecayFixed(decayFixed)
        }
        onDecayLowChanged: {
            implementation.setDecayScaleVals(decayLow, decayHigh, decayExponent)
        }
        onDecayHighChanged: {
            implementation.setDecayScaleVals(decayLow, decayHigh, decayExponent)
        }
        onDecayExponentChanged: {
            implementation.setDecayScaleVals(decayLow, decayHigh, decayExponent)
        }
        onDecayScaledChanged: {
            implementation.setDecayScaled(decayScaled)
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
                    spinBox.from: -1000
                    spinBox.to: 1000
                    spinBox.stepSize: 1
                    onParamValueChanged: {
                        if (editor.attack !== value) {
                            editor.attack = value
                        }
                    }
                }

                EditorFixedParam {
                    id: attackFixedEditor
                    label.text: qsTr("Fixed: ")
                    onFixedChanged: {
                        if (editor.attackFixed !== fixed) {
                            editor.attackFixed = fixed
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
                        implementation.setAttackIndexes(implementationMappings)
                    }
                }
            }

            EditorScaler {
                id: attackScaler
                label.text: qsTr("Attack Scaling: ")
                lowLabel.text: qsTr("Attack Low: ")
                highLabel.text: qsTr("Attack High: ")
                lowSpinBox.from: -1000
                lowSpinBox.to: 1000
                lowSpinBox.stepSize: 1
                highSpinBox.from: -1000
                highSpinBox.to: 1000
                highSpinBox.stepSize: 1

                onLowChanged:
                {
                    if(editor.attackLow !== low) {
                        editor.attackLow = low
                    }
                }
                onHighChanged:
                {
                    if(editor.attackHigh !== high) {
                        editor.attackHigh = high
                    }
                }
                onExponentChanged:
                {
                    if(editor.attackExponent !== exp) {
                        editor.attackExponent = exp
                    }
                }
                onUseScalingChanged:
                {
                    if(editor.attackScaled !== scaling) {
                        editor.attackScaled = scaling
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
                    spinBox.from: -1000
                    spinBox.to: 1000
                    spinBox.stepSize: 1
                    onParamValueChanged: {
                        if (editor.decay !== value) {
                            editor.decay = value
                        }
                    }
                }

                EditorFixedParam {
                    id: decayFixedEditor
                    label.text: qsTr("Fixed: ")
                    onFixedChanged: {
                        if (editor.decayFixed !== fixed) {
                            editor.decayFixed = fixed
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
                        implementation.setDecayIndexes(implementationMappings)
                    }
                }
            }

            EditorScaler {
                id: decayScaler
                label.text: qsTr("Decay Scaling: ")
                lowLabel.text: qsTr("Decay Low: ")
                highLabel.text: qsTr("Decay High: ")
                lowSpinBox.from: -1000
                lowSpinBox.to: 1000
                lowSpinBox.stepSize: 1
                highSpinBox.from: -1000
                highSpinBox.to: 1000
                highSpinBox.stepSize: 1

                onLowChanged:
                {
                    if(editor.decayLow !== low) {
                        editor.decayLow = low
                    }
                }
                onHighChanged:
                {
                    if(editor.decayHigh !== high) {
                        editor.decayHigh = high
                    }
                }
                onExponentChanged:
                {
                    if(editor.decayExponent !== exp) {
                        editor.decayExponent = exp
                    }
                }
                onUseScalingChanged:
                {
                    if(editor.decayScaled !== scaling) {
                        editor.decayScaled = scaling
                    }
                }
            }
        }
    }

}
