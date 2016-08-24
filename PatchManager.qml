import QtQuick 2.7

Item {

    id: root
//    state: "UNCONNECTED"
    property var patches: new Array

    function addItem(item) {
        patches.push(item)
    }


}
