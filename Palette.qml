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

    property int spawnX: 0
    property  int spawnY: 0

    signal itemCreated(var item)

    Column {

        //        Row {

        PaletteItem {
            id: osc
            componentFile: "OSC.qml"
            source: "images/OSC.png"
            onItemCreated: root.itemCreated(item)
        }

        PaletteItem {
            id: am
            componentFile: "AM.qml"
            source: "images/MOD.png"
            onItemCreated: root.itemCreated(item)
        }

        PaletteItem {
            id: aud
            componentFile: "AUD.qml"
            source: "images/AUD.png"
            onItemCreated: root.itemCreated(item)
        }

        PaletteItem {
            id: pan
            componentFile: "PAN.qml"
            source: "images/PAN.png"
            onItemCreated: root.itemCreated(item)
        }
        //        }

        //        Row {

        PaletteItem {
            id: env
            componentFile: "ENV.qml"
            source: "images/ENV.png"
            onItemCreated: root.itemCreated(item)
        }

        PaletteItem {
            id: vol
            componentFile: "VOL.qml"
            source: "images/VOL.png"
            onItemCreated: root.itemCreated(item)
        }

        PaletteItem {
            id: nse
            componentFile: "NSE.qml"
            source: "images/NSE.png"
            onItemCreated: root.itemCreated(item)
        }

        PaletteItem {
            id: eq
            componentFile: "EQ.qml"
            source: "images/EQ.png"
            onItemCreated: root.itemCreated(item)
        }

        PaletteItem {
            id: out
            componentFile: "OUT.qml"
            source: "images/OUT.png"
            onItemCreated: root.itemCreated(item)
        }

    }
}
