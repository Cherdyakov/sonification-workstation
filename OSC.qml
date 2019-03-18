import QtQuick 2.7
import SonLib 1.0
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.0
import ENUMS 0.1
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

    Editor {
        id: editor
        EditorParameter {
            id: frequency
            // Value changed from QML
            onRealValueChanged: implementation.frequency.value = realValue
            onFixedChanged: implementation.frequency.fixed = fixed
            onScaledChanged: implementation.frequency.scaled = scaled
            onScaleRealLowChanged: implementation.frequency.scaleLo = scaleRealLow
            onScaleRealHighChanged: implementation.frequency.scaleHi = scaleRealHigh
            onScaleRealExpChanged: implementation.frequency.scaleExp = scaleRealExp
            // Value changed from C++
            value: implementation.frequency.value * 100
            fixed: implementation.frequency.fixed
            scaled: implementation.frequency.scaled
            scaleLow: implementation.frequency.scaleLow * 100
            scaleHigh: implementation.frequency.scaleHigh * 100
            scaleExp: implementation.frequency.scaleExp * 100
            mapping: implementation.frequency.map


            // Value changed from C++
//            Connections {
//                 target: implementation.frequency

//                 //Either
//                 onValueChanged: frequency.value = implementation.frequency.value * 100
//                 //Or with the "setter"
////                 onValueChanged: mySpinBox.value.setRealValue(value)
//            }

            // Set map with Q_INVOKABLE function call
            onMappingChanged: {
                if(!implementation.frequency.setMap(mapping)) {
                    mapper.textColor = "tomato"
                }
                else {
                    mapper.textColor = "black"
                }
            }
        }
    }

}

