import QtQuick 2.7
import "Style.js" as Style

SynthItem {

    id: root
    label: qsTr("OUT")
    type: 0 //OUT
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

    function mute() {
        //mute children
        for(var i = 0; i < synthChildren.length; i++) {
            var synthItem = synthChildren[i]
            synthItem.muted = muted
        }
        canvas.requestPaint()
    }

    function deleteThis() {
        for(var i = 0; i < synthChildren.length; i++)
        {
            var childItem = synthChildren[i]
            childItem.removeParent(root)
            implementation.removeChild(childItem.implementation)
        }

        var idx = synthItems.indexOf(root)
        synthItems.splice(idx, 1)

        root.destroy()
        canvas.requestPaint()
    }
}
