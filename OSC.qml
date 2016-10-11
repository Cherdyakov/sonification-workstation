import QtQuick 2.7
import SonLib 1.0

SynthItem {
    id: root
    label: "OSC"
    type: SynthGraph.OSCILLATOR
    mainColor: "blue"
    textColor: "white"
    editor: oscEditor

    property int waveform: SynthItemImplementation.SINE
    property bool fixedFreq: true
    property double freq: 440
    property var dataRows: []

    SynthItemEditor {
        id: oscEditor
        z: 300
        height: parent.height - 12
        width: parent.width - 12
        radius: parent.radius - 4
        anchors.centerIn: parent
        color: "white"

    }

}


