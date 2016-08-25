import QtQuick 2.7

Item {

    id: root
    height: 30
    width: 30

    property Canvas myCanvas
    property var start
    property var end

    Component.onCompleted: {
        end = null
        console.log("patch created")
    }

}



