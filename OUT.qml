import QtQuick 2.12
import ENUMS 1.0
import "Style.js" as Style

SynthItem {

    id: root
    label: qsTr("OUT")
    type: ENUMS.TRANSPORT
    mainColor: Style.outColor
    textColor: Style.itemTextColor
    implementation: transport

    Component.onCompleted: {
        create()
    }

    function read() {

        var parents = []

        var essence = {
            "identifier": identifier,
            "type": type,
            "x": x,
            "y": y,
            "muted": muted,
            "parents": parents
        }

        return essence
    }

    function init(essence) {
        x = essence["x"]
        y = essence["y"]
        identifier = essence["identifier"]
        muted = essence["muted"]
    }

}
