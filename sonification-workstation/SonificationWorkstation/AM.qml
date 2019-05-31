import QtQuick 2.12
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.12
import SoW 1.0
import ENUMS 1.0
import "Style.js" as Style
import "SessionCode.js" as SessionCode

SynthItem {
    id: root
    label: qsTr("AM")
    type: ENUMS.AMOD
    output: ENUMS.AM
    mainColor: themeManager.amColor
    textColor: Style.itemTextColor

    Component.onCompleted: {
        create()
    }

    Editor {
        id: editor

        EditorLayout {

            EditorTitle {
                text: qsTr("AM");
            }

            EditorParameterHeader {
                text: "Frequency"
            }

            EditorFloatParameter {
                id: frequency
                // Value changed from QML
                onScaledChanged: implementation ? implementation.frequency.scaled = scaled : {}
                onScaleRealLowChanged: implementation ? implementation.frequency.scaleLow = scaleRealLow : {}
                onScaleRealHighChanged: implementation ? implementation.frequency.scaleHigh = scaleRealHigh : {}
                onScaleRealExpChanged: implementation ? implementation.frequency.scaleExp = scaleRealExp : {}
                // Value changed from C++
                scaled: implementation ? implementation.frequency.scaled : 0
                scaleLow: implementation ? implementation.frequency.scaleLow * 100 : 0
                scaleHigh: implementation ? implementation.frequency.scaleHigh * 100 : 0
                scaleExp: implementation ? implementation.frequency.scaleExp * 100 : 0
                mapper.map: implementation ? implementation.frequency.map : ""

                // Set map with Q_INVOKABLE function call and check if it is valid.
                mapper.onMapChanged: {
                    if(implementation) {
                        if(!implementation.frequency.setMap(mapper.map)) {
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
            "freqMap": frequency.mapper.map,
            "freqScaled": frequency.scaled,
            "freqScaleLow": frequency.scaleLow,
            "freqScaleHigh": frequency.scaleHigh,
            "freqScaleExponent": frequency.scaleExp
        }
        return essence
    }

    // Initialize self from JSON essence.
    function fromEssence(essence) {
        x = essence["x"]
        y = essence["y"]
        name = essence["name"]
        mute = essence["mute"]
        frequency.mapper.map = essence["freqMap"]
        frequency.scaler.scaled = essence["freqScaled"]
        frequency.scaler.low = essence["freqScaleLow"]
        frequency.scaler.high = essence["freqScaleHigh"]
        frequency.scaler.exp = essence["freqScaleExponent"]
    }

}

