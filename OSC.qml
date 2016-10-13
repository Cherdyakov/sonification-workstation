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

    Rectangle {
        id: editor
        z: 300
        height: parent.height - 12
        width: parent.width - 12
        radius: parent.radius - 4
        anchors.centerIn: parent
        color: Style.testColor//"white"
        opacity: 0

        property int waveform: SynthItemImplementation.SINE
        property bool fixedFreq: true
        property double freq: 440
        property var dataRows: []

        onWaveformChanged: {
            implementation.setWaveform(waveform)
        }

        onFixedFreqChanged: {
            implementation.setFixedFreq(fixedFreq)
        }

        onFreqChanged: {
            implementation.setFreq(freq)
        }

        ColumnLayout {
            id: layout
            anchors.centerIn: parent
            Layout.maximumWidth: parent.width - 10

            RowLayout {
                id: waveformLayout
                Label {
                    text: "Waveform: "
                }
                ComboBox {

                    id: waveformComboBox
                    model: ["Sine", "Saw", "Square"]

                    onCurrentIndexChanged: {
                        if (editor.waveform !== currentIndex) {
                            editor.waveform = currentIndex
                        }
                    }
                }
            }

            RowLayout {
                id: freqLayout
                Label {
                    text: "Frequency: "
                }
                SpinBox {
                    id: spinbox
                    editable: true
                    from: 0
                    value: 44000
                    to: 100 * 20000
                    stepSize: 1
                    anchors.centerIn: parent

                    property int decimals: 2
                    property real realValue: value / 100

                    validator: DoubleValidator {
                        bottom: Math.min(spinbox.from, spinbox.to)
                        top:  Math.max(spinbox.from, spinbox.to)
                    }

                    textFromValue: function(value, locale) {
                        return Number(value / 100).toLocaleString(locale, 'f', spinbox.decimals)
                    }

                    valueFromText: function(text, locale) {
                        return Number.fromLocaleString(locale, text) * 100
                    }
                }


            }

            RowLayout {
                id: dataLayout
            }

        }

    }

}


