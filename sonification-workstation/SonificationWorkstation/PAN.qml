import QtQuick 2.12
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.12
import SoW 1.0
import ENUMS 1.0
import "Style.js" as Style
import "SessionCode.js" as SessionCode

SynthItem {
    id: root
    label: qsTr("PAN")
    type: ENUMS.PANNER
    output: ENUMS.AUDIO

    Accessible.role: Accessible.focusable
    Accessible.name: "Pan. Pans a signal in stereo."
    Accessible.description: ""

    Component.onCompleted: {
        create()
    }

    Editor {
        id: editor

        EditorLayout {

            EditorTitle {
                text: qsTr("PAN");
            }

            EditorParameterHeader {
                text: "Pan"
            }

            EditorFloatParameter {
                id: pan
                scaler.lowSpinBox.from: -100.0
                scaler.lowSpinBox.to: 100.0
                scaler.highSpinBox.from: -100.0
                scaler.highSpinBox.to: 100.0

                // Value changed from QML
                onScaledChanged: implementation ? implementation.pan.scaled = scaled : {}
                onScaleRealLowChanged: implementation ? implementation.pan.scaleLow = scaleRealLow : {}
                onScaleRealHighChanged: implementation ? implementation.pan.scaleHigh = scaleRealHigh : {}
                onScaleRealExpChanged: implementation ? implementation.pan.scaleExp = scaleRealExp : {}
                // Value changed from C++
                scaled: implementation ? implementation.pan.scaled : 0
                scaleLow: implementation ? implementation.pan.scaleLow * 100 : 0
                scaleHigh: implementation ? implementation.pan.scaleHigh * 100 : 0
                scaleExp: implementation ? implementation.pan.scaleExp * 100 : 0
                mapper.map: implementation ? implementation.pan.map : ""

                // Set map with Q_INVOKABLE function call and check if it is valid.
                mapper.onMapChanged: {
                    if(implementation) {
                        if(!implementation.pan.setMap(mapper.map)) {
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
            "panMap": pan.mapper.map,
            "panScaled": pan.scaled,
            "panScaleLow": pan.scaleLow,
            "panScaleHigh": pan.scaleHigh,
            "panScaleExponent": pan.scaleExp
        }
        return essence
    }

    // Initialize self from JSON essence.
    function fromEssence(essence) {
        x = essence["x"]
        y = essence["y"]
        name = essence["name"]
        mute = essence["mute"]
        pan.mapper.map = essence["panMap"]
        pan.scaler.scaled = essence["panScaled"]
        pan.scaler.low = essence["panScaleLow"]
        pan.scaler.high = essence["panScaleHigh"]
        pan.scaler.exp = essence["panScaleExponent"]
    }

}

