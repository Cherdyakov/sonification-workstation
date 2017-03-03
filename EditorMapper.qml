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

    Connections {
        target: fileReader
        onQmlDatasetChanged: {
            validateMappings()
        }
    }

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
            font.pixelSize: 14

            inputMethodHints: Qt.ImhFormattedNumbersOnly
            onEditingFinished:
            {
                validateMappings()
            }

            MouseArea {
                anchors.fill: textInput
                onClicked: {
                    textInput.forceActiveFocus()
                }
            }
        }
    }

    function validateMappings()
    {
        var inString = textInput.text
        var parsedInput = getNumbers(inString)
        var clampedInput = parsedInput.filter(filterMax)
        textInput.text = getStringRange(clampedInput)
        mappingsChanged(clampedInput)
    }

    function getNumbers(stringNumbers)
    {
        var range, low, high, entry

        var trimmed = stringNumbers.trim();
        var entries = trimmed.split(',')
        var length = entries.length
        var nums = []

        for (var i = 0; i < length; i++) {
            entry = entries[i]
            entry = entry.trim()
            //test entry is positive integer
            if (filterInt(entry)) {
                nums.push(+entry)
            }
            else
            {

                //if not a number, probably it had the - and not being a negative number
                //only here do we split after we determined that the entry isn't a number
                range = entry.split('-')

                //check if what we split are both numbers, else skip
                if (!filterInt(range[0]) || !filterInt(range[1])) continue

                //force both to be numbers
                low = +range[0]
                high = +range[1]

                //since we are dealing with numbers, we could do an XOR swap
                //which is a swap that doesn't need a third variable
                //http://en.wikipedia.org/wiki/XOR_swap_algorithm
                if (high < low) {
                    low = low ^ high
                    high = low ^ high
                    low = low ^ high
                }

                if (high > dataHeight)
                {
                    high = dataHeight
                }

                if (low < 1)
                {
                    low = 1
                }

                //from low, we push up to high
                if (low > 0)
                {
                    while (low <= high) {
                        nums.push(low++)
                    }
                }
            }
        }

        //remove all duplicates
        nums = nums.filter(function(item, pos) {
            return nums.indexOf(item) === pos;
        })
        //and finally, sort
        nums.sort(sorterFunction)
        return nums
    }

    function filterInt(value) {
        if(/^(\-|\+)?([0-9]+|Infinity)$/.test(value)) {
            return (Number(value) > 0)
        }
        return NaN
    }

    function filterMax(value) {
        return (value <= dataHeight)
    }

    //let's get this one out as well
    //the simple sort() wouldn't work so instead we provide a sorter
    function sorterFunction(a, b) {
        return a - b
    }

    //for taking validated range of numbers and presenting as text
    function getStringRange(array) {
        var ranges = ''
        var rstart, rend
        for (var i = 0; i < array.length; i++) {
            rstart = array[i]
            rend = rstart
            while (array[i + 1] - array[i] === 1) {
                rend = array[i + 1] // increment the index if the numbers sequential
                i++
            }
            if(rstart === rend) {
                //start = end, one number
                if(i < array.length - 1) {
                    ranges = ranges + rstart + ','
                }
                else {
                    ranges = ranges + rstart
                }
            }
            else {
                //start != end, is a range
                if(i < array.length - 1) {
                    ranges = ranges + rstart + '-' + rend + ','
                }
                else {
                    ranges = ranges + rstart + '-' + rend
                }
            }
        }
        return ranges
    }
}
