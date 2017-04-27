import QtQuick 2.7
import "Style.js" as Style

SynthItem {
    id: root
    label: qsTr("OUT")
    type: 0 //OUT
    mainColor: Style.outColor
    textColor: Style.itemTextColor

    function create() {
        created = true
        canvas.requestPaint()
    }

    function addChild(synthItem) {
        if(transport.addChild(synthItem.implementation, synthItem.childType)) {
            //add QML child to this item's synthChildren
            synthChildren.push(synthItem)
            //add child's implementation to root of the synth transport
            synthItem.addParent(this)
        }
    }

    function removeChild(synthItem) {
        //remove from the root of the synthtransport
        transport.removeChild(synthItem.implementation)
        //remove the QML child from this item's children
        var idx = synthChildren.indexOf(synthItem)
        if(idx > -1)
        {
            synthChildren.splice(idx, 1)
        }
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
            transport.removeFromRoot(childItem.implementation)
        }

        var idx = synthItems.indexOf(root)
        synthItems.splice(idx, 1)

        root.destroy()

        console.log(synthItems.length)

        canvas.requestPaint()
    }
}
