import QtQuick 2.7

SynthItem {
    id: root
    label: "OUT"
    type: 0 //OUT
    mainColor: "cadetblue"
    textColor: "white"

    function create() {
        created = true
        canvas.requestPaint()
    }

    function addChild(synthItem) {
        console.log("OUT add")

        //add QML child to this item's synthChildren
        synthChildren.push(synthItem)
        //add child's implementation to root of the synth graph
        graph.addToRoot(synthItem.implementation)
    }

    function removeChild(synthItem) {
        //remove from the root of the synthgraph
        graph.removeFromRoot(synthItem.implementation)
        //remove the QML child from this item's children
        var idx = synthChildren.indexOf(synthItem)
        if(idx > -1)
        {
            synthChildren.splice(idx, 1)
        }
    }

    function mute() {
        console.log("OUT mute")
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
            graph.removeFromRoot(childItem.implementation)
        }

        var idx = synthWindow.synthItems.indexOf(root)
        synthWindow.synthItems.splice(idx, 1)

        root.destroy()

        console.log(synthWindow.synthItems.length)

        canvas.requestPaint()
    }
}
