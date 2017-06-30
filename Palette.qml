import QtQuick 2.0
import "Style.js" as Style


// top panel
Rectangle {
    id: root
    color: Style.paletteColor
    opacity: Style.paletteOpacity

    property int spawnX: 0
    property  int spawnY: 0

    signal itemCreated()

    Column {

        //        Row {

        PaletteItem {
            componentFile: "OSC.qml"
            source: "images/OSC.png"
            onItemClicked: { createItem(item) }
        }

        PaletteItem {
            componentFile: "AUD.qml"
            source: "images/AUD.png"
            onItemClicked: { createItem(item) }
        }

        PaletteItem {
            componentFile: "MOD.qml"
            source: "images/MOD.png"
            onItemClicked: { createItem(item) }
        }

        PaletteItem {
            componentFile: "PAN.qml"
            source: "images/PAN.png"
            onItemClicked: { createItem(item) }
        }
        //        }

        //        Row {

        PaletteItem {
            componentFile: "ENV.qml"
            source: "images/ENV.png"
            onItemClicked: { createItem(item) }
        }

        PaletteItem {
            componentFile: "VOL.qml"
            source: "images/VOL.png"
            onItemClicked: { createItem(item) }
        }

        PaletteItem {
            componentFile: "NSE.qml"
            source: "images/NSE.png"
            onItemClicked: { createItem(item) }
        }

        PaletteItem {
            componentFile: "OUT.qml"
            source: "images/OUT.png"
            onItemClicked: { createItem(item) }
        }

        //        }

    }

    function createItem(paletteItem) {
        console.log(paletteItem.componentFile)
        var component = Qt.createComponent(paletteItem.componentFile);
        console.log(component.errorString())
        if(component.status === Component.Ready) {
            var item = component.createObject(root, { "x": spawnX - Style.itemWidth / 2,
                                                  "y": spawnY - Style.itemHeight / 2 } )
            item.create();
        }
        itemCreated()
    }
}
