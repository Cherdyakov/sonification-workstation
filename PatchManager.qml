import QtQuick 2.7

Item {

    id: root
    property var patchBegin: null
//    property var patchEnd: null

    function setPatchPoint(item) {
        console.log("PatchMgr: Signal Received")

        //not currently patching, start one
        if(patchBegin === null) {
            patchBegin = item
//            patchEnd = null
            console.log(item)
        }
        else {
            //clicked on same item, cancel patching
            if (patchBegin === item) {
                patchBegin = null
//                patchEnd = null
            }
            else {
                //clicked on second item, set that
                //as patch endpoint
//                patchEnd = item
                //add endpoint to begin's children
                console.log(item)
                patchBegin.addParent(item)
                //add startpoint to end's parents
                item.addChild(patchBegin)
                //stop patching
                patchBegin = null
//                patchEnd = null
            }
        }

    }


}
