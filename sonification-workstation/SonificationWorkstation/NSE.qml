import QtQuick 2.12
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.12
import SoW 1.0
import ENUMS 1.0
import "Style.js" as Style
import "SessionCode.js" as SessionCode

SynthItem {
    id: root
    label: qsTr("NSE")
    type: ENUMS.NOISE_GEN
    output: ENUMS.AUDIO

    Component.onCompleted: {
        create()
    }

    Editor {
        id: editor

        EditorLayout {

            EditorTitle {
                text: qsTr("NSE")
            }

            EditorParameterHeader {
                text: "Noise Type"
            }

            ComboBox {
                id: noiseType
                Layout.maximumHeight: Style.editorComboBoxHeight
                Layout.fillWidth: true
                model: [qsTr("White"), qsTr("Pink"), qsTr("Brown")]
                // Value changed from QML.
                onCurrentIndexChanged: implementation ? implementation.noise.idx = currentIndex : {}
                // Value changed from C++.
                currentIndex: implementation ? implementation.noise.idx : 0

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
            "noise": noiseType.currentIndex
        }
        return essence
    }

    // Initialize self from JSON essence.
    function fromEssence(essence) {
        x = essence["x"]
        y = essence["y"]
        name = essence["name"]
        mute = essence["mute"]
        noiseType.currentIndex = essence["noise"]
    }



}


