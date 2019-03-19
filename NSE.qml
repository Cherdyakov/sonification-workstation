import QtQuick 2.12
import SoW 1.0
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.12
import "Style.js" as Style

SynthItem {
    id: root
    label: qsTr("NSE")
    type: QtTransport.NOISE
    childType: QtSynthItem.INPUT
    mainColor: Style.nseColor
    textColor: Style.itemTextColor

    Component.onCompleted: {
        create()
        noiseEditor.index = implementation.getNoise()
    }

    // return json representation of self
    function read() {

        var parents = []
        for(var i = 0; i < synthParents.length; i++) {
            var parent = synthParents[i].identifier
            parents.push(parent)
        }

        var essence = {
            "identifier": identifier,
            "type": type,
            "x": x,
            "y": y,
            "muted": implementation.getMute(),
            "parents": parents,
            "noise": implementation.getNoise()
        }

        return essence
    }

    // initialize self from json
    function init(essence) {
        x = essence["x"]
        y = essence["y"]
        identifier = essence["identifier"]
        muted = essence["muted"]
        noiseEditor.index = essence["noise"]
    }

    Editor {

        id: editor

        EditorLayout {
            id: layout
            title: label

            EditorMenuParam {
                id: noiseEditor
                label.text: qsTr("Noise Type: ")
                model: [qsTr("White"), qsTr("Pink")]

                onIndexChanged: {
                    if(implementation === null) {
                        return
                    }
                    implementation.setNoise(index)
                }
            }


        }
    }

}


