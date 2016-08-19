import QtQuick 2.7

Item {

    id: root
//    state: "UNCONNECTED"
    property var patches: new Array


    Component.onCompleted: {
        synthWindow.connections.push(this)
        console.log(synthWindow.connection.count)

    }

    function create() {
        created = true
        graph.createItem(this, type)
        synthWindow.synthItems.push(this)
        dac.inputs.push(this)
        canvas.requestPaint()
    }






}
