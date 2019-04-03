import QtQuick 2.12
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.12
import SoW 1.0
import ENUMS 1.0
import "Style.js" as Style
import "SessionCode.js" as SessionCode

SynthItem {
    id: root
    label: qsTr("ENV")
    type: ENUMS.ENVELOPE
    output: ENUMS.AUDIO
    mainColor: Style.envColor
    textColor: Style.itemTextColor

    Component.onCompleted: {
        create()
    }

    Editor {
        id: editor

        EditorLayout {

            EditorTitle {
                text: qsTr("ENV");
            }

            EditorParameterHeader {
                text: "Envelope"
            }

            EditorFloatParameter {
                id: attack
                // Value changed from QML
                onScaledChanged: implementation ? implementation.attack.scaled = scaled : {}
                onScaleRealLowChanged: implementation ? implementation.attack.scaleLow = scaleRealLow : {}
                onScaleRealHighChanged: implementation ? implementation.attack.scaleHigh = scaleRealHigh : {}
                onScaleRealExpChanged: implementation ? implementation.attack.scaleExp = scaleRealExp : {}
                // Value changed from C++
                scaled: implementation ? implementation.attack.scaled : 0
                scaleLow: implementation ? implementation.attack.scaleLow * 100 : 0
                scaleHigh: implementation ? implementation.attack.scaleHigh * 100 : 0
                scaleExp: implementation ? implementation.attack.scaleExp * 100 : 0
                mapper.map: implementation ? implementation.attack.map : ""

                // Set map with Q_INVOKABLE function call and check if it is valid.
                mapper.onMapChanged: {
                    if(implementation) {
                        if(!implementation.attack.setMap(mapper.map)) {
                            mapper.textColor = "tomato"
                        }
                        else {
                            mapper.textColor = "black"
                        }
                    }
                }
            }

            EditorParameterHeader {
                text: "Decay"
            }

            EditorFloatParameter {
                id: decay
                // Value changed from QML
                onScaledChanged: implementation ? implementation.decay.scaled = scaled : {}
                onScaleRealLowChanged: implementation ? implementation.decay.scaleLow = scaleRealLow : {}
                onScaleRealHighChanged: implementation ? implementation.decay.scaleHigh = scaleRealHigh : {}
                onScaleRealExpChanged: implementation ? implementation.decay.scaleExp = scaleRealExp : {}
                // Value changed from C++
                scaled: implementation ? implementation.decay.scaled : 0
                scaleLow: implementation ? implementation.decay.scaleLow * 100 : 0
                scaleHigh: implementation ? implementation.decay.scaleHigh * 100 : 0
                scaleExp: implementation ? implementation.decay.scaleExp * 100 : 0
                mapper.map: implementation ? implementation.decay.map : ""

                // Set map with Q_INVOKABLE function call and check if it is valid.
                mapper.onMapChanged: {
                    if(implementation) {
                        if(!implementation.decay.setMap(mapper.map)) {
                            mapper.textColor = "tomato"
                        }
                        else {
                            mapper.textColor = "black"
                        }
                    }
                }
            }
        }

    }

    // Return essence in JSON.
    function toEssence() {
        var essence = {
            "type": type,
            "name": name,
            "x": x,
            "y": y,
            "mute": mute,
            "parentNames": SessionCode.getItemNames(synthParents),
            "attMap": attack.mapper.map,
            "attScaled": attack.scaled,
            "attScaleLow": attack.scaleLow,
            "attScaleHigh": attack.scaleHigh,
            "attScaleExponent": attack.scaleExp
        }
        return essence
    }

    // Initialize self from JSON essence.
    function fromEssence(essence) {
        x = essence["x"]
        y = essence["y"]
        name = essence["name"]
        mute = essence["mute"]
        attack.mapper.map = essence["attMap"]
        attack.scaler.scaled = essence["attScaled"]
        attack.scaler.low = essence["attScaleLow"]
        attack.scaler.high = essence["attScaleHigh"]
        attack.scaler.exp = essence["attScaleExponent"]
    }

}

