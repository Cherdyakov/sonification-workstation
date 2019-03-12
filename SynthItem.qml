import QtQuick 2.7
import SonLib 1.0
import ENUMS 0.1
import "Style.js" as Style

Item {

    id: root
     z: Style.itemZ + zModifier
     width: Style.itemHeight; height: Style.itemWidth

    property int identifier: 0
    property var synthChildren: []
    property var synthParents: []
    property var mappedRows: []
    property bool muted: false
    property int type: -1 // OUT = 0, OSC = 1
    property int output: -1 // INPUT = 0
    property bool created: false
    property string label: "SON"
    property string mainColor
    property string textColor
    property QtSynthItem implementation: null // the CPP implementation of this SynthItem
    property var zModifier: root.activeFocus === true ? 10 : 0

    property alias radius: rect.radius

    signal patching(var item)
    signal selected(var item)
    signal deleted(var item)

     Component.onCompleted: {
         synthItems.push(root)
         patching.connect(patchManager.patchBegin)
         deleted.connect(patchManager.itemDeleted)
         deleted.connect(deleteItem)
         parent = workspace.contentItem
     }

    onMutedChanged: {
        mute()
    }
    onXChanged:  {
        canvas.requestPaint()
        workspace.updateRect()
    }
    onYChanged: {
        canvas.requestPaint()
        workspace.updateRect()
    }
    onWidthChanged: canvas.requestPaint()

    states: [
        State {
            name: "MAXIMIZED"
            PropertyChanges {
                target: root
                width: editor.width + Style.editorMargin
                height: editor.height + Style.editorMargin
                z: Style.itemEditorZ + zModifier
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
        if(implementation === null) {
            deleted(root);
        }
        canvas.requestPaint()
    }

    function read() {
        // must override
        // returns params for saving in session file
    }

    function init(obj) {
        // must override
        // sets params of new item created from saved sesssion file
    }

    function connectChild(synthItem) {
        //  connect implementation
        var added = implementation.connectChild(synthItem.implementation)
        if(added === true)
        {
            //  connect QML
            synthChildren.push(synthItem)
            synthItem.addParent(this)
        }
        canvas.requestPaint()
    }

    function addParent(synthItem) {
        // add QML parent
        synthParents.push(synthItem)
    }

    function disconnect(synthItem) {
        //  disconnect implementation
        implementation.disconnect(synthItem.implementation)
        // disconnect QML
        while (synthChildren.indexOf(synthItem) > -1) {
            synthChildren.splice(synthChildren.indexOf(synthItem), 1)
        }
        while (synthParents.indexOf(synthItem) > -1) {
            synthParents.splice(synthParents.indexOf(synthItem), 1)
        }
        canvas.requestPaint()
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

    Rectangle {
        id: rect
        anchors.fill: parent
        color: muted ? Style.itemMuteColor : mainColor
        radius: Style.itemMinRadius
        border.color: root.activeFocus ? Style.itemActiveFocusColor : textColor
        border.width: 4
        opacity: created ? 1 : 0.4

        MouseArea {
            id: mouseArea
            z: Style.itemZ
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
                    root.patching(root)
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
            deleted(root)
            event.accepted = true
        }

        if (event.key === Qt.Key_M) {
            muted = !muted
            event.accepted = true
        }
    }

}
