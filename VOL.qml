import QtQuick 2.12
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.12
import SoW 1.0
import ENUMS 1.0
import "Style.js" as Style
import "SessionCode.js" as SessionCode

SynthItem {
    id: root
    label: qsTr("VOL")
    type: ENUMS.VOLUME
    output: ENUMS.AUDIO
    mainColor: Style.volColor
    textColor: Style.itemTextColor

    Component.onCompleted: {
        create()
    }

    Editor {
        id: editor

        EditorLayout {

            EditorTitle {
                text: qsTr("VOL");
            }

            EditorParameterHeader {
                text: "Volume"
            }

            EditorFloatParameter {
                id: amplitude
                scaler.lowSpinBox.from: -100.0
                scaler.lowSpinBox.to: 100.0
                scaler.highSpinBox.from: -100.0
                scaler.highSpinBox.to: 100.0

                // Value changed from QML
                onScaledChanged: implementation ? implementation.amplitude.scaled = scaled : {}
                onScaleRealLowChanged: implementation ? implementation.amplitude.scaleLow = scaleRealLow : {}
                onScaleRealHighChanged: implementation ? implementation.amplitude.scaleHigh = scaleRealHigh : {}
                onScaleRealExpChanged: implementation ? implementation.amplitude.scaleExp = scaleRealExp : {}
                // Value changed from C++
                scaled: implementation ? implementation.amplitude.scaled : 0
                scaleLow: implementation ? implementation.amplitude.scaleLow * 100 : 0
                scaleHigh: implementation ? implementation.amplitude.scaleHigh * 100 : 0
                scaleExp: implementation ? implementation.amplitude.scaleExp * 100 : 0
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

