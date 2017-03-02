import QtQuick 2.7

Item {

    id: root
    property var patchBegin: null
//    property var patchEnd: null

    function setPatchPoint(item) {

        //not currently patching, start one
        if(patchBegin === null) {
            patchBegin = item
//            patchEnd = null
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
