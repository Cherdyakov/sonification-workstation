import QtQuick 2.7
import SonLib 1.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0
import "Style.js" as Style

SynthItem {
    id: root
    label: qsTr("NSE")
    type: QtTransport.NOISE
    childType: QtSynthItem.INPUT
    mainColor: Style.nseColor
    textColor: Style.itemTextColor

    Editor {

        id: editor
        property  int noise: 0

        Component.onCompleted: {
        }

        onNoiseChanged: {
            implementation.setNoise(noise)
        }

        EditorLayout {
            id: layout
            title: label

            EditorMenuParam {
                id: noiseEditor
                label: qsTr("Noise Type: ")
                model: [qsTr("White"), qsTr("Pink")]

                onValueChanged: {
                    if (editor.noise != value) {
                        editor.noise = value;
                    }
                }
            }


        }
    }

}


