import QtQuick 2.7
import SonLib 1.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0
import "Style.js" as Style

SynthItem {
    id: root
    label: "OSC"
    type: SynthGraph.OSCILLATOR
    mainColor: "blue"
    textColor: "white"

    Component.onCompleted: {

    }

    Editor {
        id: editor

        property int waveform: SynthItemImplementation.SINE
        property bool fixedFrequency: true
        property double frequency: 440
        property var dataRows: []

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

            EditorWaveform {
                onWaveformChanged: {
                    if (editor.waveform != form) {
                        editor.waveform = form
                    }
                }
            }

            EditorFrequency {
                onFrequencyChanged: {
                    if (editor.frequency != freq) {
                        editor.frequency = freq
                    }
                }
            }

            EditorFixedParam {
                text: "Fixed Frequency: "
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


