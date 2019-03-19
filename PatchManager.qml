import QtQuick 2.7
import "Style.js" as Style

Item {

    id: root

    property var patchingChild: null
    property var selectedPatch: null
    property var patches: []
    property int selectionErrorMargin: 1 + (Style.patchWidth / 2) // distance from patch considered "clicked"
    property bool patching: patchingChild ? true : false

    onActiveFocusChanged: {
        if(root.activeFocus === false) {
            selectedPatch = null
        }
        canvas.requestPaint()
    }

    Keys.onDeletePressed: {
        disconnectPatch(selectedPatch)
        deletePatch(selectedPatch)
        selectedPatch = null
        canvas.requestPaint()
    }

    function click(point) {
        selectedPatch = selectPatch(point)
        if(selectedPatch !== null) {
            root.forceActiveFocus()
        }
    }

    // Find the closest patch to point that is also
    // within the clickErrorMargin.
    function selectPatch(point) {
        var selectedPatch = null
        var distance = Number.MAX_VALUE
        for(var i = 0; i < patches.length; i++) {
            var currentDistance = distanceToPatch(point, patches[i])
            if( (currentDistance < distance) && (currentDistance < selectionErrorMargin) ) {
                distance = currentDistance
                selectedPatch = patches[i]
            }
        }
        return selectedPatch
    }

    // Start the process of pathing an item.
    function patchBegin(item) {
        // Not currently patching, start one.
        if(patchingChild === null) {
            if(item.type !== 0) { // Item is OUT (Transport), which cannot have parents.
                patchingChild = item
            }
        }
        else {
            // Clicked again on the item at the start of
            // the patch, cancel patching.
            if (patchingChild === item) {
                patchingChild = null
            }
            else {
                // Clicked on a second item. Connect first
                // item as synthChild of second.
                item.connectChild(patchingChild)

                var patch = {
                    parent: item,
                    child: patchingChild
                }

                patches.push(patch)
                // Stop patching and paint.
                patchingChild = null
                canvas.requestPaint()
            }
        }
    }

    // Returns a list of all point pairs of existing patches.
    // Used by main.qml to draw the patches on screen.
    function getPatchPoints() {
        var patchPoints = []
        for(var i = 0; i < patches.length; i++) {
            var patch = patches[i]
            var pointPair =  pointsFromPatch(patch)
            patchPoints.push(pointPair)
        }
        if(patchingChild !== null) {
            var inProgressPoints = getPatchInProgressPoints()
            patchPoints.push(inProgressPoints)
        }
        return patchPoints
    }

    // Returns points for any patch that is currenlty being created.
    function getPatchInProgressPoints() {
        if(patchingChild !== null) {
            var childPoint = centerPoint(patchingChild)
            var mousePoint = mapToItem(canvas, workspaceMouseArea.mouseX, workspaceMouseArea.mouseY)
        }
        return {
            begin: childPoint,
            end: mousePoint
        }
    }

    // Returns pair of points for given patch.
    function pointsFromPatch(patch)
    {
        var childPoint = centerPoint(patch.child)
        var parentPoint = centerPoint(patch.parent)

        return {
            begin: childPoint,
            end: parentPoint
        }
    }

    // Return point at center of item.
    function centerPoint(item)
    {
        var xCentered = item.x + item.width / 2
        var yCentered = item.y + item.height / 2
        var mappedPoint = mapFromItem(workspace.contentItem, xCentered, yCentered)
        return mappedPoint
    }

    // Connected to deleted() signal in SynthItem.
    // Deletes all patches the item was a part of.
    // Transport handles disconnection of deleted items.
    function itemDeleted(item) {
        for(var i = 0; i < patches.length; i++) {
            var patch = patches[i]
            if(patch.parent === item || patch.child === item) {
                deletePatch(patch)
            }
        }
        canvas.requestPaint()
    }

    // Disconnect the parent and child in a patch.
    function disconnectPatch(patch) {
        var parent = patch.parent
        var child = patch.child
        parent.disconnect(child)
        child.disconnect(parent)
    }

    // Delete an existing patch (does not disconnect).
    function deletePatch(patch) {
        while(patches.indexOf(patch) > -1) {
            patches.splice(patches.indexOf(patch), 1)
        }
    }

    // The distance from given point to a given patch.
    function distanceToPatch(point, patch) {
        var pointPair = pointsFromPatch(patch)
        var distance = distToSegment(point, pointPair.begin, pointPair.end)
        return distance
    }

    // Math functions used by distanceToPatch()
    function distToSegment(p, v, w) {
        return Math.sqrt(distToSegmentSquared(p, v, w))
    }

    function distToSegmentSquared(p, v, w) {
        var l2 = dist2(v, w)
        if (l2 === 0) return dist2(p, v)
        var t = ((p.x - v.x) * (w.x - v.x) + (p.y - v.y) * (w.y - v.y)) / l2
        t = Math.max(0, Math.min(1, t))
        return dist2(p, { x: v.x + t * (w.x - v.x),
                         y: v.y + t * (w.y - v.y) })
    }

    function sqr(x) {
        return x * x
    }

    function dist2(v, w) {
        return sqr(v.x - w.x) + sqr(v.y - w.y)
    }

}
