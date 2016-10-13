import QtQuick 2.7
import SonLib 1.0

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

    property alias radius: rect.radius

    signal clickedItem(var i)

    width: 64; height: 64

    Component.onCompleted: {
        synthItems.push(this)
        this.parent = workspace.contentItem
    }

    onMutedChanged: {
        mute()
    }
    onXChanged: canvas.requestPaint()
    onYChanged: canvas.requestPaint()
    onWidthChanged: canvas.requestPaint()

    states: [

        State {
            name: "MAXIMIZED"
            PropertyChanges {
                target: root
                width: 220
                height: 100
            }
            PropertyChanges {
                target: rect
                radius: 10
            }
            PropertyChanges {
                target: editor
                opacity: 1
            }
        }

    ]

    transitions: [
        Transition {
            PropertyAnimation {
                properties: "width,height,radius,x,y";
                easing.type: Easing.InOutQuad;
                duration: 80
            }
        }

    ]

    function create() {
        created = true
        implementation =  graph.createItem(this, type)
        canvas.requestPaint()
    }

    function addChild(synthItem) {
        console.log("base add")
        //add QML child to this item's synthChildren
        synthChildren.push(synthItem)
        //add child's implementation to the children
        //of this item's implementation
                implementation.addChild(synthItem.implementation, synthItem.type)
    }

    function removeChild(synthItem) {
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

    function addParent(synthItem) {
        synthParents.push(synthItem)
    }

    function removeParent(synthItem) {
        var idx = synthParents.indexOf(synthItem)
        if(idx > -1)
        {
            synthParents.splice(idx, 1)
        }
    }

    function mute() {
        console.log("base mute")
        //mute cpp counterpart
        implementation.mute(muted)

        //mute children
        for(var i = 0; i < synthChildren.length; ++i) {
            var synthItem = synthChildren[i]
            synthItem.muted = muted
        }
        canvas.requestPaint()
    }

    function deleteThis() {
        for(var i = 0; i < synthParents.length; i++)
        {
            var parentItem = synthParents[i]
            parentItem.removeChild(root)
        }

        for(i = 0; i < synthChildren.length; i++)
        {
            var childItem = synthChildren[i]
            childItem.removeParent(root)
        }

        var idx = synthWindow.synthItems.indexOf(root)
        synthWindow.synthItems.splice(idx, 1)

        root.destroy()

        console.log(synthWindow.synthItems.length)

        canvas.requestPaint()
    }


    FocusScope {
        id: scope
        anchors.fill: parent
    }

    Rectangle {
        id: rect
        z: 200
        anchors.fill: parent
        color: muted ? "darkgray" : mainColor
        radius: 100
        border.color: scope.focus ? "orange" : textColor
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

            onReleased: {
                mouseArea.Drag.drop()
            }

            onClicked: {
                //left clicked
                if(mouse.button & Qt.LeftButton) {
                    scope.focus = true
                }
                //right clicked
                if(mouse.button & Qt.RightButton) {
                    switch(root.state) {
                    case "":
                        root.state = "MAXIMIZED"
                        break
                    case "MAXIMIZED":
                        root.state = ""
                        break
                    }
                    console.log("editor:" + editor)
                    scope.focus = true
                }
            }

            onDoubleClicked: {
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
            deleteThis()
            event.accepted = true
        }

        if (event.key === Qt.Key_M) {
            muted = !muted
            event.accepted = true
        }
    }

}

