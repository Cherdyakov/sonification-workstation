import QtQuick 2.0
import "Style.js" as Style


// top panel
Rectangle {
    id: root
    color: Style.paletteColor
    opacity: Style.paletteOpacity

    Column {

        Row {

            PaletteItem {
                componentFile: "OSC.qml"
                source: "images/OSC.png"
            }

            PaletteItem {
                componentFile: "AUD.qml"
                source: "images/AUD.png"
            }

            PaletteItem {
                componentFile: "MOD.qml"
                source: "images/MOD.png"
            }

            PaletteItem {
                componentFile: "PAN.qml"
                source: "images/PAN.png"
            }
        }

        Row {

            PaletteItem {
                componentFile: "ENV.qml"
                source: "images/ENV.png"
            }

            PaletteItem {
                componentFile: "VOL.qml"
                source: "images/VOL.png"
            }

            PaletteItem {
                componentFile: "NSE.qml"
                source: "images/NSE.png"
            }

            PaletteItem {
                componentFile: "OUT.qml"
                source: "images/OUT.png"
            }

        }

    }
}
