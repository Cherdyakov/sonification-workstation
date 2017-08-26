import QtQuick 2.0
import "Style.js" as Style


// top panel
Rectangle {
    id: root
    color: Style.paletteColor
    opacity: Style.paletteOpacity
    radius: 100
    border.width: 0
    border.color: "white"

    property alias osc: osc
    property alias aud: aud
    property alias mod: mod
    property alias pan: pan
    property alias env: env
    property alias vol: vol
    property alias nse: nse
    property alias eq: eq
    property alias out: out

    property int spawnX: 0
    property  int spawnY: 0

    signal itemCreated()

    Column {

        //        Row {

        PaletteItem {
            id: osc
            componentFile: "OSC.qml"
            source: "images/OSC.png"
//            onItemClicked: { createItem(item) }
        }

        PaletteItem {
            id: aud
            componentFile: "AUD.qml"
            source: "images/AUD.png"
//            onItemClicked: { createItem(item) }
        }

        PaletteItem {
            id: mod
            componentFile: "MOD.qml"
            source: "images/MOD.png"
//            onItemClicked: { createItem(item) }
        }

        PaletteItem {
            id: pan
            componentFile: "PAN.qml"
            source: "images/PAN.png"
//            onItemClicked: { createItem(item) }
        }
        //        }

        //        Row {

        PaletteItem {
            id: env
            componentFile: "ENV.qml"
            source: "images/ENV.png"
//            onItemClicked: { createItem(item) }
        }

        PaletteItem {
            id: vol
            componentFile: "VOL.qml"
            source: "images/VOL.png"
//            onItemClicked: { createItem(item) }
        }

        PaletteItem {
            id: nse
            componentFile: "NSE.qml"
            source: "images/NSE.png"
//            onItemClicked: { createItem(item) }
        }

        PaletteItem {
            id: eq
            componentFile: "EQ.qml"
            source: "images/OUT.png"
//            onItemClicked: { createItem(item) }
        }

        PaletteItem {
            id: out
            componentFile: "OUT.qml"
            source: "images/OUT.png"
//            onItemClicked: { createItem(item) }
        }

        //        }

    }

//    function createItem(paletteItem) {
//        console.log(paletteItem.componentFile)
//        var component = Qt.createComponent(paletteItem.componentFile);
//        console.log(component.errorString())
//        if(component.status === Component.Ready) {
//            var item = component.createObject(root, { "x": spawnX - Style.itemWidth / 2,
//                                                  "y": spawnY - Style.itemHeight / 2 } )
//            item.create();
//        }
//        itemCreated()
//    }
}
