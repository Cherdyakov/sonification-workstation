import QtQuick 2.12
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.12
import SoW 1.0
import ENUMS 1.0
import "Style.js" as Style
import "SessionCode.js" as SessionCode

SynthItem {
    id: root
    label: qsTr("ENV")
    type: ENUMS.ENVELOPE
    output: ENUMS.AUDIO
    mainColor: Style.envColor
    textColor: Style.itemTextColor

    Component.onCompleted: {
        create()
    }

    Editor {
        id: editor

        EditorLayout {

            EditorTitle {
                text: qsTr("ENV");
            }

            EditorParameterHeader {
                text: "Envelope"
            }

            EditorFloatParameter {
                id: attack
                // Value changed from QML
                onScaledChanged: implementation ? implementation.attack.scaled = scaled : {}
                onScaleRealLowChanged: implementation ? implementation.attack.scaleLow = scaleRealLow : {}
                onScaleRealHighChanged: implementation ? implementation.attack.scaleHigh = scaleRealHigh : {}
                onScaleRealExpChanged: implementation ? implementation.attack.scaleExp = scaleRealExp : {}
                // Value changed from C++
                scaled: implementation ? implementation.attack.scaled : 0
                scaleLow: implementation ? implementation.attack.scaleLow * 100 : 0
                scaleHigh: implementation ? implementation.attack.scaleHigh * 100 : 0
                scaleExp: implementation ? implementation.attack.scaleExp * 100 : 0
                mapper.map: implementation ? implementation.attack.map : ""

                // Set map with Q_INVOKABLE function call and check if it is valid.
                mapper.onMapChanged: {
                    if(implementation) {
                        if(!implementation.attack.setMap(mapper.map)) {
                            mapper.textColor = "tomato"
                        }
                        else {
                            mapper.textColor = "black"
                        }
                    }
                }
            }

            EditorParameterHeader {
                text: "Decay"
            }

            EditorFloatParameter {
                id: decay
                // Value changed from QML
                onScaledChanged: implementation ? implementation.decay.scaled = scaled : {}
                onScaleRealLowChanged: implementation ? implementation.decay.scaleLow = scaleRealLow : {}
                onScaleRealHighChanged: implementation ? implementation.decay.scaleHigh = scaleRealHigh : {}
                onScaleRealExpChanged: implementation ? implementation.decay.scaleExp = scaleRealExp : {}
                // Value changed from C++
                scaled: implementation ? implementation.decay.scaled : 0
                scaleLow: implementation ? implementation.decay.scaleLow * 100 : 0
                scaleHigh: implementation ? implementation.decay.scaleHigh * 100 : 0
                scaleExp: implementation ? implementation.decay.scaleExp * 100 : 0
                mapper.map: implementation ? implementation.decay.map : ""

                // Set map with Q_INVOKABLE function call and check if it is valid.
                mapper.onMapChanged: {
                    if(implementation) {
                        if(!implementation.decay.setMap(mapper.map)) {
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
        attackEditor.value = essence["freq"]
        fixedAttackEditor.fixed = essence["freqFixed"]
        var indexes = essence["freqIndexes"]
        var stringIndexes = SessionCode.indexesToString(indexes)
        attackMapper.text = stringIndexes
        attackMapper.validateMappings()
        attackScaler.scaled = essence["freqScaled"]
        attackScaler.low = essence["freqScaleLow"]
        attackScaler.high = essence["freqScaleHigh"]
        attackScaler.exponent = essence["freqScaleExponent"]
    }

}

