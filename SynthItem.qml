import QtQuick 2.7
import son.lib 1.0

Item {

    id: root

    property var synthChildren: []
    property var synthParents: []
    property bool patching: false
    property bool muted: false
    property int type: -1 //OUT = 0, OSC = 1
    property bool created: false
    property var inputs: new Array
    property var outputs: new Array
    property string label: "SON"
    property string mainColor
    property string textColor
    property SynthItemImplementation implementation: null //the CPP implementation of this SynthItem
    property PatchManager myManager: null

    signal clickedItem(var i)

    states: [
        State {
          name: "maximized"
          PropertyChanges {
              target: rect;
              color: mainColor
              radius: 100
              border.color: textColor

          }
        }

    ]


    Component.onCompleted: {
        synthItems.push(this)
    }

    function create() {
        created = true
        implementation =  graph.createItem(this, type)
        canvas.requestPaint()
    }

    function addChild(synthItem)
    {
        //add QML child to this item's synthChildren
        synthChildren.push(synthItem)
        //add child's implementation to the children
        //of this item's implementation
        implementation.addChild(synthItem.implementation, synthItem.type)
    }

    function removeChild(synthItem)
    {
        //remove the child implementation from the
        //children of this item's implementation
        implementation.removeChild(synthItem.implementation)
        //remove the QML child from this item's children
        var idx = synthChildren.indexOf(synthItem)
        if(idx > -1)
        {
            synthChildren.splice(idx, 1)
        }
    }

    function addParent(synthItem)
    {
        synthParents.push(synthItem)
    }

    function removeParent(synthItem)
    {
        var idx = synthParents.indexOf(synthItem)
        if(idx > -1)
        {
            synthParents.splice(idx, 1)
        }
    }

    onMutedChanged: {
        implementation.mute(muted)

        //mute children
        for(var i = 0; i < synthChildren.length; ++i) {
            var synthItem = synthChildren[i]
            synthItem.muted = muted
        }
        canvas.requestPaint()
    }


    width: 64; height: 64

    onXChanged: canvas.requestPaint()
    onYChanged: canvas.requestPaint()

    FocusScope {
        id: scope
        anchors.fill: parent
    }

    Rectangle {
        id: rect
        z: 200
        anchors.fill: parent
        color: muted ? "dark gray" : mainColor
        radius: 100
        border.color: textColor
        opacity: created ? 1 : 0.4

        MouseArea {
            id: mouseArea
            acceptedButtons: Qt.LeftButton | Qt.RightButton | Qt.MiddleButton

            anchors.fill: rect

            drag.target: root
            drag.axis: Drag.XAndYAxis
            drag.minimumX: 0
            drag.minimumY: 0
            Drag.active: mouseArea.drag.active
            Drag.hotSpot.x: 36
            Drag.hotSpot.y: 32

            onReleased: mouseArea.Drag.drop()

            onClicked: {
                if(mouse.button & Qt.LeftButton) {
                    scope.focus = true
                }
                if(mouse.button & Qt.RightButton) {

                }
            }

            onDoubleClicked: {
//                console.log("Item: double click")
                patchManager.setPatchPoint(root)
                canvas.requestPaint()
                scope.focus = true
            }

        }

        Text {
            id: labelText
            text: label
            color: textColor
            anchors {
                centerIn: parent
            }
        }

    }

    Keys.onPressed: {
        if (event.key === Qt.Key_Backspace || event.key === Qt.Key_Delete) {
            console.log("Type: del")

            var parentCount = synthParents.length

            for(var i = 0; i < parentCount; i++)
            {
                var parentItem = synthParents[i]
                parentItem.removeChild(root)
            }

            var childCount = synthChildren.length
            for(var i = 0; i < childCount; i++)
            {
                var childItem = synthChildren[i]
                childItem.removeParent(root)
            }

            var idx = synthWindow.synthItems.indexOf(root)
            synthWindow.synthItems.splice(idx, 1)

            root.destroy()
            canvas.requestPaint()
            event.accepted = true
        }

        if (event.key === Qt.Key_M) {
            muted = !muted
            event.accepted = true
        }
    }

}

