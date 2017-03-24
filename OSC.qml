import QtQuick 2.7
import SonLib 1.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0
import "Style.js" as Style

SynthItem {
    id: root
    label: qsTr("OSC")
    type: QtSynthGraph.OSCILLATOR
    mainColor: Style.oscColor
    textColor: Style.itemTextColor

    Component.onCompleted: {
        console.log("OSC Created")
    }

    Editor {

        id: editor
        property int waveform: QtSynthItem.SINE
        property bool fixedFrequency: true
        property double frequency: 440

        Component.onCompleted: {
            waveformEditor.comboBox.currentIndex = waveform
            frequencyEditor.spinBox.value = frequency * 100
            fixedEditor.checkBox.checked = fixedFrequency
        }

        onWaveformChanged: {
            implementation.setWaveform(waveform)
        }

        onFixedFrequencyChanged: {
            implementation.setFixedFreqs(fixedFrequency)
        }

        onFrequencyChanged: {
            implementation.setFreq(frequency)
            console.log(frequency)
        }

        EditorLayout {
            id: layout
            title: label

            EditorWaveform {
                id: waveformEditor
                onWaveformChanged: {
                    if (editor.waveform != form) {
                        editor.waveform = form
                    }
                }
            }

            RowLayout {

                EditorFrequency {
                    id: frequencyEditor
                    onFrequencyChanged: {
                        if (editor.frequency != freq) {
                            editor.frequency = freq / 100
                        }
                    }
                }

                EditorFixedParam {
                    id: fixedEditor
                    label.text: qsTr("Fixed: ")
                    onFixedChanged: {
                        if (editor.fixedFrequency != fixed) {
                            editor.fixedFrequency = fixed
                        }
                    }
                }

            }

            EditorMapper {
                id: frequencyMapper
                label.text: qsTr("Frequency Source: ")
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


