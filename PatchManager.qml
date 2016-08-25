import QtQuick 2.7
import "patchCreation.js" as Script

Item {

    id: root
    //    state: "UNCONNECTED"
    property var patches: new Array
    property Patch patch: null


    function setPatchPoint(item) {
        console.log("PatchMgr: Signal Received")

        if(patch === null) {
            patch = Script.createPatch()
            patch.start = item
        }
        else {
            if (patch.start === item) {
                patch = null
            }
            else {
                patch.end = item
                patches.push(patch)
                patch = null
            }
        }

    }


}
