import QtQuick 2.7

Item {

    id: root
    property var patchBegin: null

    function setPatchPoint(item) {

        //not currently patching, start one
        if(patchBegin === null) {
            if(item.type !== 0) { //item is OUT, cannot have parent
                patchBegin = item
            }
        }
        else {
            //clicked on same item, cancel patching
            if (patchBegin === item) {
                patchBegin = null
            }
            else {
                //clicked on second item
                //add endpoint to begin's children
                patchBegin.addParent(item)
                //add startpoint to end's parents
                item.addChild(patchBegin)
                //stop patching
                patchBegin = null
            }
        }
    }
}
