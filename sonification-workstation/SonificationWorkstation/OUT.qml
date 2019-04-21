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

    // Return essence in JSON.
    function toEssence() {
        var essence = {
            "type": type,
            "name": name,
            "x": x,
            "y": y,
            "mute": mute
        }
        return essence
    }

    // Initialize self from JSON essence.
    function fromEssence(essence) {
        x = essence["x"]
        y = essence["y"]
        name = essence["name"]
        mute = essence["mute"]
    }

}
