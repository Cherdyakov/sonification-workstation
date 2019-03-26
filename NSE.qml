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
    mainColor: Style.nseColor
    textColor: Style.itemTextColor

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
                model: [qsTr("White"), qsTr("Pink"), qsTr("Brown")]
                // Value changed from QML.
                onCurrentIndexChanged: implementation ? implementation.noise.idx = currentIndex : {}
                // Value changed from C++.
                currentIndex: implementation ? implementation.noise.idx : 0

            }

        }
    }



}


