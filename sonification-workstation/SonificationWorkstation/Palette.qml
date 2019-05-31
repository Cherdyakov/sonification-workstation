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

        PaletteItem {
            label: "OSC"
            componentFile: "OSC.qml"
            onItemCreated: root.itemCreated(item)
        }

        PaletteItem {
            label: "NSE"
            componentFile: "NSE.qml"
            onItemCreated: root.itemCreated(item)
        }

        PaletteItem {
            label: "AUD"
            componentFile: "AUD.qml"
            onItemCreated: root.itemCreated(item)
        }

        PaletteItem {
            label: "AM"
            componentFile: "AM.qml"
            onItemCreated: root.itemCreated(item)
        }

        PaletteItem {
            label: "FM"
            componentFile: "FM.qml"
            onItemCreated: root.itemCreated(item)
        }

        PaletteItem {
            label: "VOL"
            componentFile: "VOL.qml"
            onItemCreated: root.itemCreated(item)
        }

        PaletteItem {
            label: "PAN"
            componentFile: "PAN.qml"
            onItemCreated: root.itemCreated(item)
        }

        PaletteItem {
            label: "ENV"
            componentFile: "ENV.qml"
            onItemCreated: root.itemCreated(item)
        }

        PaletteItem {
            label: "EQ"
            componentFile: "EQ.qml"
            onItemCreated: root.itemCreated(item)
        }

        PaletteItem {
            label: "OUT"
            componentFile: "OUT.qml"
            onItemCreated: root.itemCreated(item)
        }

    }
}
