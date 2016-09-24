import QtQuick 2.7

Item {

    id: root
    property var patchBegin: null
    property var patchEnd: null

    function setPatchPoint(item) {
        console.log("PatchMgr: Signal Received")

        //not currently patching, start one
        if(patchBegin === null) {
            patchBegin = item
        }
        else {
            //clicked on same item, cancel patching
            if (patchBegin === item) {
                patchBegin = null
            }
            else {
                //clicked on second item, set that
                //as patch endpoint
                patchEnd = item
                //add endpoint to begin's children
                patchBegin.children.push(item)
                //stop patching
                patchBegin = null
                patchEnd = null
            }
        }

    }


}
