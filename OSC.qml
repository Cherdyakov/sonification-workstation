import QtQuick 2.7
import SonLib 1.0
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.0
import SowEnums 0.1
import "Style.js" as Style
import "SessionCode.js" as SessionCode

SynthItem {
    id: root
    label: qsTr("OSC")
    type: SowEnums.OSCILLATOR
    output: SowEnums.AUDIO
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
            // Bind QML to C++ values
            onValueChanged: implementation.frequency.value = value
            onFixedChanged: implementation.frequency.fixed = fixed
            onScaledChanged: implementation.frequency.scaled = scaled
            onScaleLowChanged: implementation.frequency.scaleLo = scaleLow
            onScaleHighChanged: implementation.frequency.scaleHi = scaleHigh
            onScaleExpChanged: implementation.frequency.scaleExp = scaleExp
            onMappingChanged: implementation.frequency.map = mapping
            // Bind C++ to QML values
            value: implementation.frequency.value
            fixed: implementation.frequency.fixed
            scaled: implementation.frequency.scaled
            scaleLow: implementation.frequency.scaleLo
            scaleHigh: implementation.frequency.scaleHi
            scaleExp: implementation.frequency.scaleExp
            mapping: implementation.frequency.map
        }
    }

}

