import QtQuick 2.12
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.12
import SoW 1.0
import ENUMS 1.0
import "Style.js" as Style
import "SessionCode.js" as SessionCode

SynthItem {
    id: root
    label: qsTr("AUD")
    type: ENUMS.AUDIFIER
    output: ENUMS.AUDIO
    mainColor: Style.audColor
    textColor: Style.itemTextColor

    Component.onCompleted: {
        create()
    }

    Editor {
        id: editor

        EditorLayout {

            EditorTitle {
                text: qsTr("AUD");
            }

            EditorParameterHeader {
                text: "Amplitude"
            }

            EditorFloatParameter {
                id: amplitude
                 // Value changed from C++
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
                scaler.enabled: false;
                scaler.visible: false;
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
            "ampMap": amplitude.mapper.map
        }
        return essence
    }

    // Initialize self from JSON essence.
    function fromEssence(essence) {
        x = essence["x"]
        y = essence["y"]
        name = essence["name"]
        mute = essence["mute"]
        frequency.mapper.map = essence["ampMap"]
    }

}

