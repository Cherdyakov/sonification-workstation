import QtQuick
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

        SowPaletteItem {
            label: "OSC"
            componentFile: "OSC.qml"
        }

        SowPaletteItem {
            label: "NSE"
            componentFile: "NSE.qml"
        }

        SowPaletteItem {
            label: "AUD"
            componentFile: "AUD.qml"
        }

        SowPaletteItem {
            label: "AM"
            componentFile: "AM.qml"
        }

        SowPaletteItem {
            label: "FM"
            componentFile: "FM.qml"
        }

        SowPaletteItem {
            label: "VOL"
            componentFile: "VOL.qml"
        }

        SowPaletteItem {
            label: "PAN"
            componentFile: "PAN.qml"
        }

        SowPaletteItem {
            label: "ENV"
            componentFile: "ENV.qml"
        }

        SowPaletteItem {
            label: "EQ"
            componentFile: "EQ.qml"
        }

        SowPaletteItem {
            label: "OUT"
            componentFile: "OUT.qml"
        }

    }
}
