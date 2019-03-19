import QtQuick 2.12
import SoW 1.0
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.12
import "Style.js" as Style
import "SessionCode.js" as SessionCode

SynthItem {
    id: root
    label: qsTr("AUD")
    type: QtTransport.AUDIFIER
    childType: QtSynthItem.INPUT
    mainColor: Style.audColor
    textColor: Style.itemTextColor


    Component.onCompleted: {
        create()
    }

    // return json representation of self
    function read() {

        var parents = []
        for(var i = 0; i < synthParents.length; i++) {
            var parent = synthParents[i].identifier
            parents.push(parent)
        }

        var audIndexes = implementation.getAudIndexes()
        // remove keys from audIndexes and store in js array
        var audIndexesArray = Object.keys(audIndexes).map(function(k) { return audIndexes[k] });

        var essence = {
            "identifier": identifier,
            "type": type,
            "x": x,
            "y": y,
            "muted": implementation.getMute(),
            "parents": parents,
            "audIndexes": audIndexesArray,
        }

        return essence
    }

    // initialize self from json
    function init(essence) {
        x = essence["x"]
        y = essence["y"]
        identifier = essence["identifier"]
        muted = essence["muted"]
        var indexes = essence["audIndexes"]
        var stringIndexes = SessionCode.indexesToString(indexes)
        audificationMapper.text = stringIndexes
        audificationMapper.validateMappings()
    }


    Editor {

        id: editor

        EditorLayout {
            id: layout
            title: label

            EditorMapper {
                id: audificationMapper
                label.text: qsTr("Amplitude Source: ")
                maxIndexes: 128
                onMappingsChanged:
                {
                    var implementationMappings = mappings.map( function(value) {
                        return value - 1;
                    } )
                    implementation.setAudIndexes(implementationMappings, QtSynthItem.AUDIFICATION)
                }
            }
        }
    }

}


