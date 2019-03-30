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

    // return json representation of self
    function toEssence() {

        var parents = []
        for(var i = 0; i < synthParents.length; i++) {
            var parent = synthParents[i].identifier
            parents.push(parent)
        }

        var freqIndexes = implementation.getFreqIndexes()
        // remove keys from freqIndexes and store in js array
        var freqIndexesArray = Object.keys(freqIndexes).map(function(k) { return freqIndexes[k] });

        var essence = {
            "identifier": identifier,
            "type": type,
            "x": x,
            "y": y,
            "muted": implementation.getMute(),
            "parents": parents,
            "freq": implementation.getFreq(),
            "freqIndexes": freqIndexesArray,
            "freqFixed": implementation.getFreqFixed(),
            "freqScaled": implementation.getFreqScaled(),
            "freqScaleLow": implementation.getFreqScaleLow(),
            "freqScaleHigh": implementation.getFreqScaleHigh(),
            "freqScaleExponent": implementation.getFreqScaleExponent()
        }
        return essence
    }

    // initialize self from json
    function init(essence) {
        x = essence["x"]
        y = essence["y"]
        identifier = essence["identifier"]
        muted = essence["muted"]
        amplitudeEditor.value = essence["freq"]
        fixedAmplitudeEditor.fixed = essence["freqFixed"]
        var indexes = essence["freqIndexes"]
        var stringIndexes = SessionCode.indexesToString(indexes)
        amplitudeMapper.text = stringIndexes
        amplitudeMapper.validateMappings()
        amplitudeScaler.scaled = essence["freqScaled"]
        amplitudeScaler.low = essence["freqScaleLow"]
        amplitudeScaler.high = essence["freqScaleHigh"]
        amplitudeScaler.exponent = essence["freqScaleExponent"]
    }

}

