import QtQuick 2.12
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.12
import SoW 1.0
import ENUMS 1.0
import "Style.js" as Style
import "SessionCode.js" as SessionCode

SynthItem {
    id: root
    label: qsTr("EQ")
    type: ENUMS.EQUALIZER
    output: ENUMS.AUDIO
    mainColor: Style.eqColor
    textColor: Style.itemTextColor

    Component.onCompleted: {
        create()
    }

    Editor {
        id: editor

        EditorLayout {

            EditorTitle {
                text: qsTr("EQ");
            }

            EditorParameterHeader {
                text: qsTr("Filter Type")
            }

            ComboBox {
                id: filterType
                Layout.maximumHeight: Style.editorComboBoxHeight
                Layout.fillWidth: true
                model: [qsTr("Low Pass"), qsTr("High Pass"), qsTr("Band Pass"), qsTr("Notch")]
                // Value changed from QML.
                onCurrentIndexChanged: implementation ? implementation.type.idx = currentIndex : {}
                // Value changed from C++.
                currentIndex: implementation ? implementation.type.idx : 0
            }

            EditorParameterHeader {
                text: qsTr("Frequency")
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

            EditorParameterHeader {
                text: qsTr("Resonance")
            }

            EditorFloatParameter {
                id: resonance
                scaler.lowSpinBox.from: 100
                scaler.highSpinBox.from: 100
                // Value changed from QML
                onScaledChanged: implementation ? implementation.resonance.scaled = scaled : {}
                onScaleRealLowChanged: implementation ? implementation.resonance.scaleLow = scaleRealLow : {}
                onScaleRealHighChanged: implementation ? implementation.resonance.scaleHigh = scaleRealHigh : {}
                onScaleRealExpChanged: implementation ? implementation.resonance.scaleExp = scaleRealExp : {}
                // Value changed from C++
                scaled: implementation ? implementation.resonance.scaled : 0
                scaleLow: implementation ? implementation.resonance.scaleLow * 100 : 0
                scaleHigh: implementation ? implementation.resonance.scaleHigh * 100 : 0
                scaleExp: implementation ? implementation.resonance.scaleExp * 100 : 0
                mapper.map: implementation ? implementation.resonance.map : ""

                // Set map with Q_INVOKABLE function call and check if it is valid.
                mapper.onMapChanged: {
                    if(implementation) {
                        if(!implementation.resonance.setMap(mapper.map)) {
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

    // Return essence in JSON.
    function toEssence() {
        var essence = {
            "type": type,
            "name": name,
            "x": x,
            "y": y,
            "mute": mute,
            "parentNames": SessionCode.getItemNames(synthParents),
            // Filter type.
            "type:": filterType.currentIndex,
            // Frequency parameter.
            "freqMap": frequency.mapper.map,
            "freqScaled": frequency.scaled,
            "freqScaleLow": frequency.scaleLow,
            "freqScaleHigh": frequency.scaleHigh,
            "freqScaleExponent": frequency.scaleExp,
            // Resonance Parameter.
            "resMap": resonance.mapper.map,
            "resScaled": resonance.scaled,
            "resScaleLow": resonance.scaleLow,
            "resScaleHigh": resonance.scaleHigh,
            "resScaleExponent": resonance.scaleExp
        }
        return essence
    }

    // Initialize self from JSON essence.
    function fromEssence(essence) {
        x = essence["x"]
        y = essence["y"]
        name = essence["name"]
        mute = essence["mute"]
        // Filter type.
        filterType.currentIndex = essence["type"]
        // frequency parameter.
        frequency.mapper.map = essence["freqMap"]
        frequency.scaler.scaled = essence["freqScaled"]
        frequency.scaler.low = essence["freqScaleLow"]
        frequency.scaler.high = essence["freqScaleHigh"]
        frequency.scaler.exp = essence["freqScaleExponent"]
        // Resonance parameter.
        resonance.mapper.map = essence["resMap"]
        resonance.scaler.scaled = essence["resScaled"]
        resonance.scaler.low = essence["resScaleLow"]
        resonance.scaler.high = essence["resScaleHigh"]
        resonance.scaler.exp = essence["resScaleExponent"]

    }

}

