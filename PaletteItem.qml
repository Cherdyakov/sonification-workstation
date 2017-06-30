import QtQuick 2.7
//import "itemCreation.js" as Code

Image {
    id: paletteItem

    property string componentFile
    property string image

    signal itemClicked(var item)

    source: image
    width: 50
    height: 50

    MouseArea {
        anchors.fill: parent

        onPressed: {
            console.log("clicked")
            itemClicked(paletteItem);
        }
    }
}

