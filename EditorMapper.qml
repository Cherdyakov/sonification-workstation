import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import "Style.js" as Style

RowLayout {
    id: root
    Layout.maximumHeight: Style.editorRowHeight

    property string parameterName: "none"
    property alias label: label
    property alias textInput: textInput

    signal mappingsChanged(var mappings)

    EditorLabel {
        id: label
        text: qsTr("Source: ")
        Layout.maximumHeight: Style.editorRowHeight
        Layout.preferredWidth: Style.editorLabelWidth
        Layout.fillWidth: true
    }
    Rectangle {
        id: textInputRect
        color: Style.editorTextInputColor
        height:Style.editorRowHeight
        width: Style.editorControlWidth

        TextInput {
            id: textInput
            anchors.fill: parent
            inputMethodHints: Qt.ImhFormattedNumbersOnly
            onAccepted:
            {
                var input = text;
                var stringList = input.replace(/ /g,'/')
                stringList = stringList.replace(/,/g,'/')
                stringList = stringList.replace(/\r?\n|\r/g,'/')
                stringList = stringList.split('/')

                var numbers = stringList.map(Number)
                numbers = numbers.filter(Number)

                //remove invalid numbers (0)
                var index = numbers.indexOf(0);
                while(index !== -1)
                {
                    numbers.splice(index, 1);
                    index = numbers.indexOf(0)
                }

                editor.dataRows = numbers
                console.log("numbers: " + numbers)

                var numString
                for(var i = 0; i < editor.dataRows.length; i++)
                {
                    numString =  numString + (editor.dataRows[i].toString() + " ")
                }
                console.log("numString: " + numString)
                textInput.text = numString

                mappingsChanged(numString)
            }
        }
    }
}
