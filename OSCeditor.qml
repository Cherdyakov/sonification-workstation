import QtQuick 2.7
import SonLib 1.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0

SynthItemEditor {
    id: root
    z: 300
    height: parent.height - 12
    width: parent.width - 12
    radius: parent.radius - 4
    anchors.centerIn: parent
    color: "white"

    property int waveform: SynthItemImplementation.SINE
    property bool fixedFreq: true
    property double freq: 440
    property var dataRows: []

    onWaveformChanged: {

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

                Component.onCompleted: {
                    currentIndex = waveform
                }

                id: waveformComboBox
                model: ["Sine", "Saw", "Square"]

                onCurrentIndexChanged: {
                    if (waveform !== currentIndex) {
                        waveform = currentIndex
                    }
                }
            }
        }

        RowLayout {
            id: freqLayout
        }

        RowLayout {
            id: dataLayout
        }

    }

}
