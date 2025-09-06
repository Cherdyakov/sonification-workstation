import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import SoW 1.0
import ENUMS 1.0
import "Style.js" as Style
import "SessionCode.js" as SessionCode

SynthItem {
    id: root
    label: qsTr("VOL")
    type: ENUMS.VOLUME
    output: ENUMS.AUDIO

    Accessible.role: Accessible.focusable
    Accessible.name: "Volume. Controls the amplitude of a signal."
    Accessible.description: ""

    Component.onCompleted: {
        create()
    }

    Editor {
        id: editor

        EditorLayout {

            EditorTitle {
                text: qsTr("VOL");
            }

            EditorParameterHeader {
                text: "Volume"
            }

            EditorFloatParameter {
                id: amplitude
                scaler.lowSpinBox.from: -100.0
                scaler.lowSpinBox.to: 100.0
                scaler.highSpinBox.from: -100.0
                scaler.highSpinBox.to: 100.0

                // Value changed from QML
                onScaledChanged: implementation ? implementation.amplitude.scaled = scaled : {}
                onScaleRealLowChanged: implementation ? implementation.amplitude.scaleLow = scaleRealLow : {}
                onScaleRealHighChanged: implementation ? implementation.amplitude.scaleHigh = scaleRealHigh : {}
                onScaleRealExpChanged: implementation ? implementation.amplitude.scaleExp = scaleRealExp : {}
                // Value changed from C++
                scaled: implementation ? implementation.amplitude.scaled : 0
                scaleLow: implementation ? implementation.amplitude.scaleLow * 100 : 0
                scaleHigh: implementation ? implementation.amplitude.scaleHigh * 100 : 0
                scaleExp: implementation ? implementation.amplitude.scaleExp * 100 : 0
                mapper.map: implementation ? implementation.amplitude.map : ""

                // Set map with Q_INVOKABLE function call and check if it is valid.
                mapper.onMapChanged: {
                    if(implementation) {
                        if(!implementation.amplitude.setMap(mapper.map)) {
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
            "ampMap": amplitude.mapper.map,
            "ampScaled": amplitude.scaled,
            "ampScaleLow": amplitude.scaleLow,
            "ampScaleHigh": amplitude.scaleHigh,
            "ampScaleExponent": amplitude.scaleExp
        }
        return essence
    }

    // Initialize self from JSON essence.
    function fromEssence(essence) {
        x = essence["x"]
        y = essence["y"]
        name = essence["name"]
        mute = essence["mute"]
        amplitude.mapper.map = essence["ampMap"]
        amplitude.scaler.scaled = essence["ampScaled"]
        amplitude.scaler.low = essence["ampScaleLow"]
        amplitude.scaler.high = essence["ampScaleHigh"]
        amplitude.scaler.exp = essence["ampScaleExponent"]
    }

}

