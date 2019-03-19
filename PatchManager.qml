import QtQuick 2.7
import "Style.js" as Style

Item {

    id: root

    property var patchingChild: null
    property var selectedPatch: null
    property var patches: []
    property int margin: 1 + (Style.patchWidth / 2) // distance from patch considered "clicked"

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

    // find closest patch to point
    function selectPatch(point) {
        var selectedPatch = null
        var distance = Number.MAX_VALUE
        for(var i = 0; i < patches.length; i++) {
            var currentDistance = distanceToPatch(point, patches[i])
            if(currentDistance < distance) {
                distance = currentDistance
                selectedPatch = patches[i]
            }
        }
        return selectedPatch
    }

    // a patch in progress
    function patchBegin(item) {
        //not currently patching, start one
        if(patchingChild === null) {
            if(item.type !== 0) { //item is OUT, cannot have parent
                patchingChild = item
            }
        }
        else {
            //clicked on same item, cancel patching
            if (patchingChild === item) {
                patchingChild = null
            }
            else {
                //clicked on second item
                //add startpoint to end's parents
                item.connectChild(patchingChild)

                var patch = {
                    parent: item,
                    child: patchingChild
                }
                patches.push(patch)
                //stop patching
                patchingChild = null
                canvas.requestPaint()
            }
        }
    }

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

    // takes a patch
    // returns pair of points
    function pointsFromPatch(patch)
    {
        var childPoint = centerPoint(patch.child)
        var parentPoint = centerPoint(patch.parent)

        return {
            begin: childPoint,
            end: parentPoint
        }
    }

    // return point at center of item
    function centerPoint(item)
    {
        var xCentered = item.x + item.width / 2
        var yCentered = item.y + item.height / 2
        var mappedPoint = mapFromItem(workspace.contentItem, xCentered, yCentered)
        return mappedPoint
    }

    function itemDeleted(item) {
        for(var i = 0; i < patches.length; i++) {
            var patch = patches[i]
            if(patch.parent === item || patch.child === item) {
                deletePatch(patch)
            }
        }
        canvas.requestPaint()
    }

    function disconnectPatch(patch) {
        var parent = patch.parent
        var child = patch.child
        parent.disconnect(child)
        child.disconnect(parent)
    }

    function deletePatch(patch) {
        while(patches.indexOf(patch) > -1) {
            patches.splice(patches.indexOf(patch), 1)
        }
    }

    function distanceToPatch(point, patchPoints) {
        var v = patchPoints.child
        var w = patchPoints.parent

        var distance = distToSegment(point, v, w)
        return distance
    }

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
