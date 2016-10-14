import QtQuick 2.7
import SonLib 1.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0
import "Style.js" as Style

SynthItem {
    id: root
    label: "OSC"
    type: SynthGraph.OSCILLATOR
    mainColor: Style.oscColor
    textColor: Style.itemTextColor

    Component.onCompleted: {
    }

    Editor {

        id: editor
        property int waveform: SynthItemImplementation.SINE
        property bool fixedFrequency: true
        property double frequency: 440
        property var dataRows: []

        Component.onCompleted: {
            waveformEditor.comboBox.currentIndex = waveform
            frequencyEditor.spinBox.value = frequency * 100
            fixedEditor.checkBox.checked = fixedFrequency
        }

        onWaveformChanged: {
            implementation.setWaveform(waveform)
        }

        onFixedFrequencyChanged: {
            implementation.setFixedFreq(fixedFrequency)
        }

        onFrequencyChanged: {
            implementation.setFreq(frequency)
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
                label.text: "Fixed Frequency: "
                onFixedChanged: {
                    if (editor.fixedFrequency != fixed) {
                        editor.fixedFrequency = fixed
                    }
                }
            }

            RowLayout {
                id: dataLayout
            }

        }
    }

}


