import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.11
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
        function ondatasetImportReady() {
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

