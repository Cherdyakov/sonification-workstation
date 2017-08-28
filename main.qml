import QtQuick.Controls 2.2
import QtQuick 2.7
import QtQuick.Layouts 1.0
import "SessionCode.js" as SessionCode
import "Style.js" as Style
import "Utils.js" as Utils

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

    function deleteItem(item) {
        var idx = synthItems.indexOf(item)
        if(idx > -1) {
            synthItems.splice(idx, 1)
        }
        transport.deleteItem(item.implementation)
        item.destroy()
    }

    Flickable {
        id: workspace
        z: Style.workspaceZ
        clip: true
        boundsBehavior: Flickable.DragAndOvershootBounds
        anchors {
            top: root.top
            left: root.left
            right: root.right
            bottom: root.bottom
        }

        function updateRect() {
            var rect = Utils.itemsRect(synthItems)
            contentHeight = rect.yMax + Style.itemHeight
            contentWidth = rect.xMax + Style.itemWidth
        }

        onContentXChanged: {
            canvas.requestPaint()
        }
        onContentYChanged: {
            canvas.requestPaint()
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
        z: -100
        parent: workspace
        anchors.fill: parent
        hoverEnabled: true
        acceptedButtons: Qt.LeftButton | Qt.RightButton

        onMouseXChanged: if(patchManager.patching) { canvas.requestPaint() }
        onMouseYChanged: if(patchManager.patching) { canvas.requestPaint() }

        onClicked: {
            workspace.forceActiveFocus()
            if(mouse.button === Qt.RightButton) {
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
            else if(mouse.button === Qt.LeftButton) {
                var point = {
                    x: mouse.x,
                    y: mouse.y
                }
                patchManager.click(point)
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

            var patchPoints = patchManager.getDrawPoints(synthItems)

            for (var i = 0; i < patchPoints.length; i++)
            {
                var points = patchPoints[i]
                drawPatch(ctx, points, Style.patchColor)
            }

            var selectedPatch = patchManager.selectedPatch
            if(selectedPatch !== null) {
                points = patchManager.pointsFromPatch(selectedPatch)
                drawPatch(ctx, points, Style.itemActiveFocusColor)
            }
        }

        function drawPatch(ctx, points, style) {
            // set color
            ctx.strokeStyle = style
            ctx.lineWidth = Style.patchWidth
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

    //Audio output (root of transport)
    OUT {
        type: 0
        id: dac
        created: true
        x: workspace.width / 2 - dac.width / 2
        y: workspace.height - 100
    }

}

