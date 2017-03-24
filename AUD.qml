import QtQuick 2.7
import SonLib 1.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0
import "Style.js" as Style

SynthItem {
    id: root
    label: qsTr("AUD")
    type: QtSynthGraph.AUDIFIER
    mainColor: Style.audColor
    textColor: Style.itemTextColor

    Component.onCompleted: {
    }

    Editor {

        id: editor

        Component.onCompleted: {

        }

        EditorLayout {
            id: layout
            title: label

            EditorMapper {
                id: audificationMapper
                label.text: qsTr("Audification Source: ")
                onMappingsChanged:
                {
                    if(root.mappedRows !== mappings) {
                        root.mappedRows = mappings
                        var implementationMappings = mappings.map( function(value) {
                            return value - 1;
                        } )
                        implementation.setIndexes(implementationMappings)
                    }
                }
            }
        }
    }

}


