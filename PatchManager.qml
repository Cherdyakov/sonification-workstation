import QtQuick 2.7

Item {

    id: root

    property var patchInProgressParent: null
    property var selectedPatch: null
    property var patches: []
    property int margin: 8 // distance from patch considered "clicked"

    function click(point) {
        var closest = selectPatch(point)
        selectedPatch = closest
    }

    // find closest patch to point
    function selectPatch(point) {
        var selectPatch = null
        var distance = Number.MAX_VALUE
        for(var i = 0; i < patches.length; i++) {
            var currentPatch = patches[i]
            var patchPoints = pointsFromPatch(currentPatch)
            var currentDistance = distanceToPatch(point, patchPoints)
            if(currentDistance < distance) {
                distance = currentDistance
                selectPatch = currentPatch
            }
        }
       if(distance < margin) {
           return selectPatch
       }
       else {
           return null
       }
    }

    // a patch in progress
    function patchBegin(item) {
        //not currently patching, start one
        if(patchInProgressParent === null) {
            if(item.type !== 0) { //item is OUT, cannot have parent
                patchInProgressParent = item
            }
        }
        else {
            //clicked on same item, cancel patching
            if (patchInProgressParent === item) {
                patchInProgressParent = null
            }
            else {
                //clicked on second item
                //add startpoint to end's parents
                item.addChild(patchInProgressParent)
                //stop patching
                patchInProgressParent = null
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
                    child: childItem
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
        if(patchInProgressParent !== null) {
            var inProgressPoints = getPatchInProgressPoints()
            patchPoints.push(inProgressPoints)
        }
        return patchPoints
    }

    function getPatchInProgressPoints() {
        if(patchInProgressParent !== null) {
            var beginPoint = centerPoint(patchInProgressParent)
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
        console.log(item)
        var xCentered = item.x + item.width / 2
        var yCentered = item.y + item.height / 2
        var mappedPoint = mapFromItem(workspace.contentItem, xCentered, yCentered)
        return mappedPoint
    }

    function distanceToPatch(point, patchPoints)
    {
        var x0 = point.x
        var y0 = point.y
        var x1 = patchPoints.begin.x
        var y1 = patchPoints.begin.y
        var x2 = patchPoints.end.x
        var y2 = patchPoints.end.y

        var distance = Math.abs((y2-y1)*x0 - (x2-x1)*y0 + x2*y1 - y2*x1) / Math.sqrt((y2-y1)*(y2-y1) + (x2-x1)*(x2-x1))
        console.log(distance)
        return distance
    }

}
