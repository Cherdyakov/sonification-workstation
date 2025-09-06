import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "Style.js" as Style

ColumnLayout {
    id: root
    Layout.maximumHeight: Style.editorRowHeight * 2

    property alias text: textInput.text
    property alias textColor: textInput.color
    property string map: ""

    onMapChanged: textInput.text = map;

    // Force map re-evaluation on new Dataset.
    Connections {
        target: transport
        function onDatasetImportReady() {
            var tempMap = map
            map = ""
            map = tempMap
        }
    }

    Rectangle {
        id: textInputRect
        color: Style.editorTextInputColor
        height:Style.editorRowHeight
        width: Style.editorRowWidth
        Layout.fillWidth: true

        TextInput {
            id: textInput
            anchors.fill: parent
            font.pixelSize: 14
            onEditingFinished: {
                map = text
            }

            MouseArea {
                anchors.fill: textInput
                onClicked: {
                    textInput.forceActiveFocus()
                }
            }
        } // textInput
    } // textInputRect
} // root

