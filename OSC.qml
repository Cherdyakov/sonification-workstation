import QtQuick 2.12
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.12
import SoW 1.0
import ENUMS 1.0
import "Style.js" as Style
import "SessionCode.js" as SessionCode

SynthItem {
    id: root
    label: qsTr("OSC")
    type: ENUMS.OSCILLATOR
    output: ENUMS.AUDIO
    mainColor: Style.oscColor
    textColor: Style.itemTextColor

    Component.onCompleted: {
        create()
    }

    Editor {
        id: editor

        EditorLayout {

            EditorTitle {
                text: qsTr("OSC");
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

    // return json representation of self
    function read() {

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
        frequencyEditor.value = essence["freq"]
        fixedFrequencyEditor.fixed = essence["freqFixed"]
        var indexes = essence["freqIndexes"]
        var stringIndexes = SessionCode.indexesToString(indexes)
        frequencyMapper.text = stringIndexes
        frequencyMapper.validateMappings()
        frequencyScaler.scaled = essence["freqScaled"]
        frequencyScaler.low = essence["freqScaleLow"]
        frequencyScaler.high = essence["freqScaleHigh"]
        frequencyScaler.exponent = essence["freqScaleExponent"]
    }

}

