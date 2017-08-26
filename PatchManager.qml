import QtQuick 2.7

Item {

    id: root

    property var activePatcher: null

    // a patch in progress
    function patchBegin(item) {
        //not currently patching, start one
        if(activePatcher === null) {
            if(item.type !== 0) { //item is OUT, cannot have parent
                activePatcher = item
            }
        }
        else {
            //clicked on same item, cancel patching
            if (activePatcher === item) {
                activePatcher = null
            }
            else {
                //clicked on second item
                //add startpoint to end's parents
                item.addChild(activePatcher)
                //stop patching
                activePatcher = null
            }
        }
    }

    // returns array of point pairs
    function getDrawPoints(items) {
        var patches = getPatches(items)
        var points = getPatchPoints(patches)
        return points
    }

    // takes array of Synthitems
    // returns array of patches between them
    function getPatches(items) {
        var patches = []
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
                patches.push(patch)
            }
        }
        return patches
    }

    function getPatchPoints(patches) {
        var patchPoints = []
        for(var i = 0; i < patches.length; i++) {
            var patch = patches[i]
            var pointPair =  pointsFromPatch(patch)
            patchPoints.push(pointPair)
        }
        if(activePatcher !== null) {
            var activePatchPoints = getActivePatchPoints()
            patchPoints.push(activePatchPoints)
        }
        return patchPoints
    }

    function getActivePatchPoints() {
        if(activePatcher !== null) {
            var beginPoint = centerPoint(activePatcher)
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

}
