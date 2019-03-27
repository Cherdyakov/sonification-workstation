import QtQuick.Controls 2.2
import QtQuick 2.12
import QtQuick.Layouts 1.0
import "SessionCode.js" as SessionCode
import "Style.js" as Style
import "Utils.js" as Utils

Rectangle
{
    id: root
    color: Style.workspaceColor
    anchors.fill: parent

    // Holds every item in the workspace for iterating.
    property var synthItems: []
    // Canvas for drawing patches.
    property alias canvas: canvas
    property alias workspace: workspace

    // Flickable widget container, where SynthItems are manipulated.
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

        // This item establishes the upper left
        // corner of the contentItem.childrenRect
        Item {
            x: 0
            y: 0
        }
    } // workspace

    // Activate the workspace with mouse input.
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

        // Popup menu of SynthItems, drag and drop from the menu
        // into workspace to instantiate.
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
        } // itemPopup

    } // workspaceMouseArea

    // Canvas on which patches between synthItems are drawn.
    Canvas {
        id: canvas
        z: 0
        anchors.fill: workspace

        // Actually tracks and holds patches between SynthItems.
        PatchManager {
            id: patchManager
            anchors.fill: parent
        }

        onPaint: {
            // Get context to draw with.
            var ctx = getContext("2d")
            // Clear canvas, so we aren't drawing on top of last frame.
            ctx.clearRect(0, 0, canvas.width, canvas.height)

            var patchPoints = patchManager.getPatchPoints()

            for (var i = 0; i < patchPoints.length; i++)
            {
                var points = patchPoints[i]
                drawPatch(ctx, points, false)
            }

            // Draw the currently selected patch in a different color.
            if(patchManager.selectedPatch !== null) {
                points = patchManager.pointsFromPatch(patchManager.selectedPatch)
                drawPatch(ctx, points, true)
            }
        }

        function drawPatch(ctx, points, selected) {

            var outColor
            var inColor

            // Draw the currently selected patch in a different color.
            if(selected) {
                outColor = Style.patchSelectedOutColor
                inColor = Style.patchSelectedInColor
            }
            else {
                outColor = Style.patchOutColor
                inColor = Style.patchInColor
            }

            var x0 = points.child.x
            var y0 = points.child.y
            var x1 = points.parent.x
            var y1 = points.parent.y

            var gradient = ctx.createLinearGradient(x0, y0, x1, y1);
            gradient.addColorStop(Style.patchInColorStop, outColor);
            gradient.addColorStop(Style.patchOutColorStop, inColor);
            // set color
            ctx.strokeStyle = gradient
            ctx.lineWidth = Style.patchWidth
            // begin new drawing path
            ctx.beginPath()
            // line start point
            ctx.moveTo(x0, y0)
            // line end point
            ctx.lineTo(x1, y1)
            // stroke using line width and stroke style
            ctx.stroke()
        }
    } // canvas

    // Connected to the deleted() signal of SynthItems.
    function deleteItem(item) {
        while (synthItems.indexOf(item) > -1) {
            synthItems.splice(synthItems.indexOf(item), 1)
        }
        item.destroy()
    }

    // Get the SynthTree as json and return to C++.
    function synthTreeString() {
        var treeData = SessionCode.treeToJson(synthItems)
        var stringTree = JSON.stringify(treeData)
        return stringTree
    }

    // Wipe the current SynthItem tree and create a new
    // one from a json object.
    function synthTreeFromJson(json) {
        // Destroy all existing SynthItems.
        synthItems.forEach(function(item) {
            item.deleteThis()
        })
        SessionCode.jsonToTree(json)
        patchManager.regeneratePatches(synthItems)
    }

} // root

