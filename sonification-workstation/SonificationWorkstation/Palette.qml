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

    Column {

        PaletteItem {
            label: "OSC"
            componentFile: "OSC.qml"
        }

        PaletteItem {
            label: "NSE"
            componentFile: "NSE.qml"
        }

        PaletteItem {
            label: "AUD"
            componentFile: "AUD.qml"
        }

        PaletteItem {
            label: "AM"
            componentFile: "AM.qml"
        }

        PaletteItem {
            label: "FM"
            componentFile: "FM.qml"
        }

        PaletteItem {
            label: "VOL"
            componentFile: "VOL.qml"
        }

        PaletteItem {
            label: "PAN"
            componentFile: "PAN.qml"
        }

        PaletteItem {
            label: "ENV"
            componentFile: "ENV.qml"
        }

        PaletteItem {
            label: "EQ"
            componentFile: "EQ.qml"
        }

        PaletteItem {
            label: "OUT"
            componentFile: "OUT.qml"
        }

    }
}
