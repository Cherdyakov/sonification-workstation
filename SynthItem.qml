import QtQuick 2.7
import SonLib 1.0
import "Style.js" as Style

Item {

    id: root

    property var synthChildren: []
    property var synthParents: []
    property var mappedRows: []
    property int rowCount: 0
    property bool patching: false
    property bool muted: false
    property int type: -1 // OUT = 0, OSC = 1
    property int childType: -1 // INPUT = 0
    property bool created: false
    property var inputs: new Array
    property var outputs: new Array
    property string label: "SON"
    property string mainColor
    property string textColor
    property QtSynthItem implementation: null // the CPP implementation of this SynthItem

    property alias radius: rect.radius

    signal clickedItem(var i)
    signal implementationSet()

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
                width: editor.width + Style.editorMargin
                height: editor.height + Style.editorMargin
            }
            PropertyChanges {
                target: rect
                radius: Style.itemMaxRadius
            }
            PropertyChanges {
                target: editor
                opacity: 1
                enabled: true
            }
        }

    ]

    transitions: [
        Transition {
            PropertyAnimation {
                properties: "width,height,radius,x,y"
                easing.type: Easing.InOutQuad
                duration: 80
            }
            PropertyAnimation {
                properties: "opacity"
                from: ""
                to: "MAXIMIZED"
                easing.type: Easing.InQuint
                duration: 160
            }
            PropertyAnimation {
                properties: "opacity"
                from: "MAXIMIZED"
                to: ""
                easing.type: Easing.OutQuint
                duration: 10
            }
        }

    ]

    function create() {
        created = true
        implementation = transport.createItem(type)
        implementationSet()
        canvas.requestPaint()
    }

    function addChild(synthItem) {
        //  add child's implementation to the children
        //  of this item's implementation
        var added = implementation.addChild(synthItem.implementation, synthItem.childType)
        if(added === true)
        {
            //  add QML child to this item's synthChildren
            synthChildren.push(synthItem)
            //  add this to the new child's parents
            synthItem.addParent(this)
        }
        canvas.requestPaint()
    }

    function removeChild(synthItem) {
        //  remove the child implementation from the
        //  children of this item's implementation
        implementation.removeChild(synthItem.implementation)
        // remove the QML child from this item's children
        var idx = synthChildren.indexOf(synthItem)
        if(idx > -1)
        {
            synthChildren.splice(idx, 1)
        }
        canvas.requestPaint()
    }

    function addParent(synthItem) {
        // add QML parent to this item's synthParents
        synthParents.push(synthItem)
    }

    function removeParent(synthItem) {
        // remove parent's implementation from
        // this implementation's parent's
        implementation.removeParent(synthItem.implementation);
        // remove parent from this item's synthParents
        var idx = synthParents.indexOf(synthItem)
        if(idx > -1)
        {
            synthParents.splice(idx, 1)
        }
    }

    function mute() {
        // mute cpp counterpart
        implementation.mute(muted)

        // mute children
        for(var i = 0; i < synthChildren.length; i++) {
            var synthItem = synthChildren[i]
            synthItem.muted = muted
        }
        canvas.requestPaint()
    }

    function deleteThis() {

        implementation.deleteItem()

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

        var idx = synthItems.indexOf(root)
        synthItems.splice(idx, 1)

        root.destroy()
        canvas.requestPaint()
    }

    Rectangle {
        id: rect
        z: Style.itemZ
        anchors.fill: parent
        color: muted ? Style.itemMuteColor : mainColor
        radius: Style.itemMinRadius
        border.color: root.activeFocus ? "orange" : textColor
        border.width: 4
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
            Drag.hotSpot.x: 32
            Drag.hotSpot.y: 32

            onReleased: {
                mouseArea.Drag.drop()
            }

            onClicked: {
                // left clicked
                if(mouse.button & Qt.LeftButton) {
                    root.forceActiveFocus()
                }
                // right clicked
                if(mouse.button & Qt.RightButton) {
                    patchManager.setPatchPoint(root)
                    canvas.requestPaint()
                    root.forceActiveFocus()
                }
            }

            onDoubleClicked: {
                if(type === 0) { //  item is OUT, has no editor
                    return
                }

                switch(root.state) {
                case "":
                    root.state = "MAXIMIZED"
                    break
                case "MAXIMIZED":
                    root.state = ""
                    break
                }
                root.forceActiveFocus()
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

