import QtQuick 2.7
import SonLib 1.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0
import "Style.js" as Style
import "SessionCode.js" as SessionCode

SynthItem {
    id: root
    label: qsTr("ENV")
    type: QtTransport.ENVELOPE
    childType: QtSynthItem.INPUT
    mainColor: Style.envColor
    textColor: Style.itemTextColor

    Component.onCompleted: {
        create()
        attackEditor.value = implementation.getAttack()
        attackFixedEditor.fixed = implementation.getAttackFixed()
        attackScaler.scaled = implementation.getAttackScaled()
        attackScaler.low = implementation.getAttackScaleLow()
        attackScaler.high = implementation.getAttackScaleHigh()
        attackScaler.exponent = implementation.getAttackScaleExponent()
        decayEditor.value = implementation.getDecay()
        decayFixedEditor.fixed = implementation.getDecayFixed()
        decayScaler.scaled = implementation.getDecayScaled()
        decayScaler.low = implementation.getDecayScaleLow()
        decayScaler.high = implementation.getDecayScaleHigh()
        decayScaler.exponent = implementation.getDecayScaleExponent()
    }

    // return json representation of self
    function read() {

        var parents = []
        for(var i = 0; i < synthParents.length; i++) {
            var parent = synthParents[i].identifier
            parents.push(parent)
        }

        var attackIndexes = implementation.getAttackIndexes()
        // remove keys from attackIndexes and store in js array
        var attackIndexesArray = Object.keys(attackIndexes).map(function(k) { return attackIndexes[k] });

        var decayIndexes = implementation.getDecayIndexes()
        // remove keys from decayIndexes and store in js array
        var decayIndexesArray = Object.keys(decayIndexes).map(function(k) { return decayIndexes[k] });


        var essence = {
            "identifier": identifier,
            "type": type,
            "x": x,
            "y": y,
            "muted": implementation.getMute(),
            "parents": parents,
            "attack": implementation.getAttack(),
            "attackIndexes": attackIndexesArray,
            "attackFixed": implementation.getAttackFixed(),
            "attackScaled": implementation.getAttackScaled(),
            "attackScaleLow": implementation.getAttackScaleLow(),
            "attackScaleHigh": implementation.getAttackScaleHigh(),
            "attackScaleExponent": implementation.getAttackScaleExponent(),
            "decay": implementation.getDecay(),
            "decayIndexes": decayIndexesArray,
            "decayFixed": implementation.getDecayFixed(),
            "decayScaled": implementation.getDecayScaled(),
            "decayScaleLow": implementation.getDecayScaleLow(),
            "decayScaleHigh": implementation.getDecayScaleHigh(),
            "decayScaleExponent": implementation.getDecayScaleExponent()
        }

        return essence
    }

    // initialize self from json
    function init(essence) {
        x = essence["x"]
        y = essence["y"]
        identifier = essence["identifier"]
        muted = essence["muted"]
        attackEditor.value = essence["attack"]
        attackFixedEditor.fixed = essence["attackFixed"]
        var indexes = essence["attackIndexes"]
        var stringIndexes = SessionCode.indexesToString(indexes)
        attackMapper.text = stringIndexes
        attackMapper.validateMappings()
        attackScaler.scaled = essence["attackScaled"]
        attackScaler.low = essence["attackScaleLow"]
        attackScaler.high = essence["attackScaleHigh"]
        attackScaler.exponent = essence["attackScaleExponent"]
        decayEditor.value = essence["decay"]
        decayFixedEditor.fixed = essence["decayFixed"]
        indexes = essence["decayIndexes"]
        stringIndexes = SessionCode.indexesToString(indexes)
        decayMapper.text = stringIndexes
        decayMapper.validateMappings()
        decayScaler.scaled = essence["decayScaled"]
        decayScaler.low = essence["decayScaleLow"]
        decayScaler.high = essence["decayScaleHigh"]
        decayScaler.exponent = essence["decayScaleExponent"]
    }

    Editor {

        id: editor

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
                    from: 0
                    to: 100
                    stepSize: 0.1
                    onValueChanged: {
                        implementation.setAttack(value)
                    }
                }

                EditorFixedParam {
                    id: attackFixedEditor
                    label.text: qsTr("Fixed: ")
                    onFixedChanged: {
                        implementation.setAttackFixed(fixed)
                    }
                }

            }

            EditorMapper {
                id: attackMapper
                label.text: qsTr("Attack Source: ")
                maxIndexes: 128
                onMappingsChanged:
                {
                    var implementationMappings = mappings.map(function(value) {
                        return value - 1
                    } )
                    if(implementation !== null) {
                        implementation.setAttackIndexes(implementationMappings)
                    }
                }
            }

            EditorScaler {
                id: attackScaler
                label.text: qsTr("Attack Scaling: ")
                lowLabel.text: qsTr("Attack Low: ")
                highLabel.text: qsTr("Attack High: ")
                lowFrom: 0
                lowTo: 100
                lowStepSize: 0.1
                highFrom: 0
                highTo: 100
                highStepSize: 0.1

                onLowChanged:
                {
                    implementation.setAttackScaleLow(low)
                }
                onHighChanged:
                {
                    implementation.setAttackScaleHigh(high)
                }
                onExponentChanged:
                {
                    implementation.setAttackScaleExponent(exponent)
                }
                onScaledChanged:
                {
                    implementation.setAttackScaled(scaled)
                }
            }

            //
            // DECAY PARAMETER
            //
            RowLayout {

                EditorDoubleParam {
                    id: decayEditor
                    label.text: "Decay: "
                    from: -100
                    to: 100
                    stepSize: 0.1
                    onValueChanged: {
                        implementation.setDecay(value)
                    }
                }

                EditorFixedParam {
                    id: decayFixedEditor
                    label.text: qsTr("Fixed: ")
                    onFixedChanged: {
                        implementation.setDecayFixed(fixed)
                    }
                }

            }

            EditorMapper {
                id: decayMapper
                label.text: qsTr("Decay Source: ")
                maxIndexes: 128
                onMappingsChanged:
                {
                    var implementationMappings = mappings.map(function(value) {
                        return value - 1
                    } )
                    if(implementation !== null) {
                        implementation.setDecayIndexes(implementationMappings)
                    }
                }
            }

            EditorScaler {
                id: decayScaler
                label.text: qsTr("Decay Scaling: ")
                lowLabel.text: qsTr("Decay Low: ")
                highLabel.text: qsTr("Decay High: ")
                lowFrom: 0
                lowTo: 100
                lowStepSize: 0.1
                highFrom: 0
                highTo: 100
                highStepSize: 0.1

                onLowChanged:
                {
                    implementation.setDecayScaleLow(low)
                }
                onHighChanged:
                {
                    implementation.setDecayScaleHigh(high)
                }
                onExponentChanged:
                {
                    implementation.setDecayScaleExponent(exponent)
                }
                onScaledChanged:
                {
                    implementation.setDecayScaled(scaled)
                }
            }
        }
    }

}
