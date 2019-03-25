import QtQuick 2.12
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.12
import SoW 1.0
import ENUMS 1.0
import "Style.js" as Style
import "SessionCode.js" as SessionCode

SynthItem {
    id: root
    label: qsTr("PAN")
    type: ENUMS.PANNER
    output: ENUMS.AUDIO
    mainColor: Style.panColor
    textColor: Style.itemTextColor

    Component.onCompleted: {
        create()
    }

    Editor {
        id: editor

        EditorLayout {

            EditorTitle {
                text: qsTr("PAN");
            }

            EditorParameterHeader {
                text: "Pan"
            }

            EditorFloatParameter {
                id: pan
                scaler.lowSpinBox.from: -100.0
                scaler.lowSpinBox.to: 100.0
                scaler.highSpinBox.from: -100.0
                scaler.highSpinBox.to: 100.0

                // Value changed from QML
                onScaledChanged: implementation ? implementation.pan.scaled = scaled : {}
                onScaleRealLowChanged: implementation ? implementation.pan.scaleLow = scaleRealLow : {}
                onScaleRealHighChanged: implementation ? implementation.pan.scaleHigh = scaleRealHigh : {}
                onScaleRealExpChanged: implementation ? implementation.pan.scaleExp = scaleRealExp : {}
                // Value changed from C++
                scaled: implementation ? implementation.pan.scaled : 0
                scaleLow: implementation ? implementation.pan.scaleLow * 100 : 0
                scaleHigh: implementation ? implementation.pan.scaleHigh * 100 : 0
                scaleExp: implementation ? implementation.pan.scaleExp * 100 : 0
                mapper.map: implementation ? implementation.pan.map : ""

                // Set map with Q_INVOKABLE function call and check if it is valid.
                mapper.onMapChanged: {
                    if(implementation) {
                        if(!implementation.pan.setMap(mapper.map)) {
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
        panEditor.value = essence["freq"]
        fixedPanEditor.fixed = essence["freqFixed"]
        var indexes = essence["freqIndexes"]
        var stringIndexes = SessionCode.indexesToString(indexes)
        panMapper.text = stringIndexes
        panMapper.validateMappings()
        panScaler.scaled = essence["freqScaled"]
        panScaler.low = essence["freqScaleLow"]
        panScaler.high = essence["freqScaleHigh"]
        panScaler.exponent = essence["freqScaleExponent"]
    }

}

