import QtQuick.Controls 2.2
import QtQuick 2.7
import QtQuick.Layouts 1.0
import "SessionCode.js" as SessionCode

Rectangle
{
    id: root
    color: "light grey"
    anchors.fill: parent

    property int dataHeight: 0
    // holds every item in the workspace for iterating
    property var synthItems: []
    //canvas for drawing connections
    property alias canvas: canvas
    property alias workspace: workspace

    Component.onCompleted: {
        dac.patching.connect(patchManager.patchBegin)
        synthItems.push(dac)
    }

    Connections {
        target: fileReader
        onQmlDatasetChanged: {
            dataHeight = height
        }
    }

    // get tree as json and return to C++ land
    function readTree() {
        var treeData = SessionCode.readTree(synthItems)
        var stringTree = JSON.stringify(treeData)
        return stringTree
    }

    function createTree(obj) {
        SessionCode.destroyItems(synthItems)
        SessionCode.createTree(obj)
    }


    Flickable {
        id: workspace
        clip: true
        z: 100
        boundsBehavior: Flickable.DragAndOvershootBounds
        contentHeight: contentItem.childrenRect.height + 20
        contentWidth: contentItem.childrenRect.width + 20

        onContentXChanged: canvas.requestPaint()
        onContentYChanged: canvas.requestPaint()

        anchors {
            top: root.top
            left: root.left
            right: root.right
            bottom: root.bottom
        }

        //This item establishes the upper left
        //corner of the contentItem.childrenRect
        Item {
            x: 0
            y: 0
        }

    }

    MouseArea {
        id: workspaceMouseArea
        hoverEnabled: true
        anchors.fill: workspace
        acceptedButtons: Qt.RightButton

        onMouseXChanged: if(patchManager.patchBegin) { canvas.requestPaint() }
        onMouseYChanged: if(patchManager.patchBegin) { canvas.requestPaint() }

        onClicked: {
            if(itemPopup.visible) {
                itemPopup.close()
            }
            else {
                itemPopup.x = mouse.x
                itemPopup.y = mouse.y - (itemPopup.height / 2)
                palette.spawnX = mouse.x
                palette.spawnY = mouse.y
                itemPopup.open()
            }
        }

        Popup {
            id: itemPopup
            height: palette.height
            width: palette.width
            closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

            background: Rectangle {
                opacity: 0
            }

            Palette {
                id: palette
                height: childrenRect.height
                width: childrenRect.width
                onItemCreated: {
                    synthItems.push(item)
                    item.patching.connect(patchManager.patchBegin)
                }
            }
        }
    }

    //canvas on which the connections are drawn
    Canvas {
        id: canvas
        z: 0
        anchors.fill: workspace

        PatchManager {
            id: patchManager
            anchors.fill: parent
        }

        onPaint: {
            // get context to draw with
            var ctx = getContext("2d")
            // clear canvas
            ctx.clearRect(0, 0, canvas.width, canvas.height)
            // setup the stroke
            ctx.lineWidth = 4
            ctx.strokeStyle = "chartreuse"

            var pointPairs = patchManager.getDrawPoints(synthItems)

            for (var i = 0; i < pointPairs.length; i++)
            {
                var points = pointPairs[i]
                // begin new drawing path
                ctx.beginPath()
                // line start point
                ctx.moveTo(points.begin.x,points.begin.y)
                // line end point
                ctx.lineTo(points.end.x,points.end.y)
                // stroke using line width and stroke style
                ctx.stroke()
            }
        }
    }

    //Audio output (root of transport)
    OUT {
        type: 0
        id: dac
        created: true
        x: workspace.width / 2 - dac.width / 2
        y: workspace.height - 100
    }

}

