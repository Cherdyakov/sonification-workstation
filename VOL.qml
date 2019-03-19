import QtQuick 2.12
import SoW 1.0
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.12
import "Style.js" as Style
import "SessionCode.js" as SessionCode

SynthItem {
    id: root
    label: qsTr("VOL")
    type: QtTransport.VOLUME
    childType: QtSynthItem.INPUT
    mainColor: Style.volColor
    textColor: Style.itemTextColor

    Component.onCompleted: {
        create()
        volumeEditor.value = implementation.getVolume()
        fixedEditor.fixed = implementation.getVolumeFixed()
        volumeScaler.low = implementation.getVolumeScaleLow()
        volumeScaler.high = implementation.getVolumeScaleHigh()
        volumeScaler.exponent = implementation.getVolumeScaleExponent()
        volumeScaler.scaled = implementation.getVolumeScaled()
    }

    // return json representation of self
    function read() {

        var parents = []
        for(var i = 0; i < synthParents.length; i++) {
            var parent = synthParents[i].identifier
            parents.push(parent)
        }

        var volumeIndexes = implementation.getVolumeIndexes()
        // remove keys from volumeIndexes and store in js array
        var volumeIndexesArray = Object.keys(volumeIndexes).map(function(k) { return volumeIndexes[k] });

        var essence = {
            "identifier": identifier,
            "type": type,
            "x": x,
            "y": y,
            "muted": implementation.getMute(),
            "parents": parents,
            "volume": implementation.getVolume(),
            "volumeIndexes": volumeIndexesArray,
            "volumeFixed": implementation.getVolumeFixed(),
            "volumeScaled": implementation.getVolumeScaled(),
            "volumeScaleLow": implementation.getVolumeScaleLow(),
            "volumeScaleHigh": implementation.getVolumeScaleHigh(),
            "volumeScaleExponent": implementation.getVolumeScaleExponent()
        }

        return essence
    }

    // initialize self from json
    function init(essence) {
        x = essence["x"]
        y = essence["y"]
        identifier = essence["identifier"]
        muted = essence["muted"]
        volumeEditor.value = essence["volume"]
        var indexes = essence["volumeIndexes"]
        var stringIndexes = SessionCode.indexesToString(indexes)
        volumeMapper.text = stringIndexes
        volumeMapper.validateMappings()
        fixedEditor.fixed = essence["volumeFixed"]
        volumeScaler.scaled = essence["volumeScaled"]
        volumeScaler.low = essence["volumeScaleLow"]
        volumeScaler.high = essence["volumeScaleHigh"]
        volumeScaler.exponent = essence["volumeScaleExponent"]
    }

    Editor {

        id: editor

        EditorLayout {
            id: layout
            title: label

            RowLayout {

                EditorDoubleParam {
                    id: volumeEditor
                    from: 0
                    to: 1
                    stepSize: 0.01
                    onValueChanged: {
                        implementation.setVolume(value)
                    }
                }

                EditorFixedParam {
                    id: fixedEditor
                    label.text: qsTr("Fixed: ")
                    onFixedChanged: {
                        implementation.setVolumeFixed(fixed)
                    }
                }

            }

            EditorMapper {
                id: volumeMapper
                label.text: qsTr("Volume Source: ")
                onMappingsChanged:
                {
                    var implementationMappings = mappings.map(function(value) {
                        return value - 1
                    } )
                    if(implementation !== null) {
                        implementation.setVolumeIndexes(implementationMappings)
                    }
                }
            }

            EditorScaler {
                id: volumeScaler
                label.text: qsTr("Volume Scaling: ")
                lowLabel.text: qsTr("Volume Low: ")
                highLabel.text: qsTr("Volume High: ")
                lowFrom: 0
                lowTo: 1
                lowStepSize: 0.01
                highFrom: 0
                highTo: 1
                highStepSize: 0.01

                onLowChanged:
                {
                    implementation.setVolumeScaleLow(low)
                }
                onHighChanged:
                {
                    implementation.setVolumeScaleHigh(high)
                }
                onExponentChanged:
                {
                    implementation.setVolumeScaleExponent(exponent)
                }
                onScaledChanged:
                {
                    implementation.setVolumeScaled(scaled)
                }
            }
        }
    }

}


