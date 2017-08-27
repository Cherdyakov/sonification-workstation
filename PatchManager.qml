import QtQuick 2.7

Item {

    id: root

    property var activePatchParent: null
    property var selectedPatch: null
    property var patches: []
    property int margin: 5 // distance from patch considered "clicked"

    function click(point) {
        var closest = closestPatch(point)
        if(closest.distance < margin) {
            closest.patch.active = true
            selectedPatch = closest
        }
        else if(selectedPatch !== null) {
            selectedPatch.active = false
            selectedPatch = null
        }
    }

    // find closest patch to point
    function closestPatch(point) {
        var closestPatch = null
        var distance = Number.MAX_VALUE
        for(var i = 0; i < patches.length; i++) {
            var currentPatch = patches[i]
            var currentDistance = distanceToPatch(point, currentPatch)
            if(currentDistance < distance) {
                distance = currentDistance
                closestPatch = currentPatch
            }
        }
        return {
            patch: closestPatch,
            distance: distance
        }
    }

    // a patch in progress
    function patchBegin(item) {
        //not currently patching, start one
        if(activePatchParent === null) {
            if(item.type !== 0) { //item is OUT, cannot have parent
                activePatchParent = item
            }
        }
        else {
            //clicked on same item, cancel patching
            if (activePatchParent === item) {
                activePatchParent = null
            }
            else {
                //clicked on second item
                //add startpoint to end's parents
                item.addChild(activePatchParent)
                //stop patching
                activePatchParent = null
            }
        }
    }

    // returns array of point pairs
    function getDrawPoints(items) {
        patches = []
        patches = getPatches(items)
        var points = getPatchPoints(patches)
        return points
    }

    // takes array of Synthitems
    // returns array of patches between them
    function getPatches(items) {
        var newPatches = []
        for(var i = 0; i < items.length; i++)
        {
            var parentItem = items[i]
            for (var j = 0; j < parentItem.synthChildren.length; j++)
            {
                var childItem = parentItem.synthChildren[j]
                var patch = {
                    parent: parentItem,
                    child: childItem,
                    active: false
                }
                newPatches.push(patch)
            }
        }
        return newPatches
    }

    function getPatchPoints(patches) {
        var patchPoints = []
        for(var i = 0; i < patches.length; i++) {
            var patch = patches[i]
            var pointPair =  pointsFromPatch(patch)
            patchPoints.push(pointPair)
        }
        if(activePatchParent !== null) {
            var activePatchPoints = getActivePatchPoints()
            patchPoints.push(activePatchPoints)
        }
        return patchPoints
    }

    function getActivePatchPoints() {
        if(activePatchParent !== null) {
            var beginPoint = centerPoint(activePatchParent)
            var endPoint = mapToItem(canvas, workspaceMouseArea.mouseX, workspaceMouseArea.mouseY)
        }
        return {
            begin: beginPoint,
            end: endPoint
        }
    }

    // takes a patch
    // returns pair of points
    function pointsFromPatch(patch)
    {
        var beginPoint = centerPoint(patch.parent)
        var endPoint = centerPoint(patch.child)

        return {
            begin: beginPoint,
            end: endPoint
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

    function distanceToPatch(point, patchPoints)
    {
        x0 = point.x
        y0 = point.y
        x1 = patchPoints.beginPoint.x
        y1 = patchPoints.beginPoint.y
        x2 = patchPoints.endPoint.x
        y2 = patchPoints.endPoint.y

        var distance = Math.abs((y2-y1)*x0 - (x2-x1)*y0 + x2*y1 - y2*x1) / Math.sqrt((y2-y1)*(y2-y1) + (x2-x1)*(x2-x1))
        return distance
    }

}
