//import QtQuick.Controls 1.4
import QtQuick.Controls 2.2
import QtQuick 2.7
import QtQuick.Layouts 1.0

Rectangle
{
    signal quit()

    id: root
    color: "light grey"
    anchors.fill: parent

    property int dataHeight: 0
    // holds every item in the workspace for iterating
    property var synthItems: []
    //canvas for drawing connections
    property alias canvas: canvas
    property alias workspace: workspace

    Connections {
        target: fileReader
        onQmlDatasetChanged: {
            dataHeight = height
        }
    }

    // top panel
    Rectangle {
        id: toolBox

        height: 70
        color: "gray"
        anchors { right: parent.right; top: parent.top; left: parent.left }

        Row {
            id: palette
            anchors.centerIn: parent
            spacing: 1

            PaletteItem {
                anchors.verticalCenter: parent.verticalCenter
                componentFile: "OSC.qml"
                source: "images/oscIcon.png"
                image: "images/oscIcon.png"
            }

            PaletteItem {
                anchors.verticalCenter: parent.verticalCenter
                componentFile: "OUT.qml"
                source: "images/oscIcon.png"
                image: "images/oscIcon.png"
            }

            PaletteItem {
                anchors.verticalCenter: parent.verticalCenter
                componentFile: "AUD.qml"
                source: "images/oscIcon.png"
                image: "images/oscIcon.png"
            }

            PaletteItem {
                anchors.verticalCenter: parent.verticalCenter
                componentFile: "MOD.qml"
                source: "images/oscIcon.png"
                image: "images/oscIcon.png"
            }

            PaletteItem {
                anchors.verticalCenter: parent.verticalCenter
                componentFile: "OUT.qml"
                source: "images/oscIcon.png"
                image: "images/oscIcon.png"
            }

            PaletteItem {
                anchors.verticalCenter: parent.verticalCenter
                componentFile: "PAN.qml"
                source: "images/oscIcon.png"
                image: "images/oscIcon.png"
            }

            PaletteItem {
                anchors.verticalCenter: parent.verticalCenter
                componentFile: "ENV.qml"
                source: "images/oscIcon.png"
                image: "images/oscIcon.png"
            }

            PaletteItem {
                anchors.verticalCenter: parent.verticalCenter
                componentFile: "VOL.qml"
                source: "images/oscIcon.png"
                image: "images/oscIcon.png"
            }

            PaletteItem {
                anchors.verticalCenter: parent.verticalCenter
                componentFile: "NSE.qml"
                source: "images/oscIcon.png"
                image: "images/oscIcon.png"
            }
        }
    }

    Flickable {
        id: workspace
        clip: true
        z: 100
        boundsBehavior: Flickable.DragAndOvershootBounds
        contentHeight: contentItem.childrenRect.height + 20
        contentWidth: contentItem.childrenRect.width + 20

        onContentXChanged: canvas.requestPaint()
        onContentYChanged: canvas.requestPaint()

        anchors {
            top: toolBox.bottom
            left: root.left
            right: root.right
            bottom: root.bottom
        }

        //This item establishes the upper left
        //corner of the contentItem.childrenRect
        Item {
            x: 0
            y: 0
        }

    }

    MouseArea {
        id: workspaceMouseArea
        hoverEnabled: true
        anchors.fill: workspace
        acceptedButtons: Qt.RightButton

        onMouseXChanged: if(patchManager.patchBegin) { canvas.requestPaint() }
        onMouseYChanged: if(patchManager.patchBegin) { canvas.requestPaint() }

        onClicked: {
            itemPopup.x = mouse.x
            itemPopup.y = mouse.y
            itemPopup.open()
        }

        Popup {
            id: itemPopup
            height: 100
            width: 100
            closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
            Button {
                text: "button"
                onClicked: itemPopup.close()
            }
        }
    }

    //canvas on which the connections are drawn
    Canvas {
        id: canvas
        z: 0
        anchors.fill: workspace

        onPaint: {
            // get context to draw with
            var ctx = getContext("2d")
            // clear canvas
            ctx.clearRect(0, 0, canvas.width, canvas.height)
            // setup the stroke
            ctx.lineWidth = 4
            ctx.strokeStyle = "chartreuse"

            // get each patch
            var itemCount = synthItems.length

            for(var i = 0; i < itemCount; i++)
            {
                var parentItem = synthItems[i]

                if (parentItem.synthChildren)
                {
                    var numChildren = parentItem.synthChildren.length

                    for (var j = 0; j < numChildren; j++)
                    {
                        var childItem = parentItem.synthChildren[j]

                        var startPoint = mapFromItem(workspace.contentItem, parentItem.x, parentItem.y)
                        var beginX = startPoint.x + parentItem.width / 2
                        var beginY = startPoint.y + parentItem.height / 2
                        var endPoint = mapFromItem(workspace.contentItem, childItem.x, childItem.y)
                        var endX = endPoint.x + childItem.width / 2
                        var endY = endPoint.y + childItem.height / 2

                        // begin a new path to draw
                        ctx.beginPath()
                        // line start point
                        ctx.moveTo(beginX,beginY)
                        // line end point
                        ctx.lineTo(endX,endY)
                        // stroke using line width and stroke style
                        ctx.stroke()
                    }
                }

                if (patchManager.patchBegin)
                {
                    var beginning = patchManager.patchBegin
                    startPoint = mapFromItem(workspace.contentItem, beginning.x, beginning.y)
                    beginX = startPoint.x + beginning.width / 2
                    beginY = startPoint.y + beginning.height / 2

                    endPoint = mapToItem(canvas, workspaceMouseArea.mouseX, workspaceMouseArea.mouseY)
                    endX = endPoint.x
                    endY = endPoint.y

                    // begin a new path to draw
                    ctx.beginPath()
                    // line start point
                    ctx.moveTo(beginX,beginY)
                    // line end point
                    ctx.lineTo(endX,endY)
                    // stroke using line width and stroke style
                    ctx.stroke()
                }
            }
        }
    }

    //Audio output (root of transport)
    OUT {
        type: 0
        id: dac
        created: true
        x: workspace.width / 2 - dac.width / 2
        y: workspace.height - 100
    }

    PatchManager {
        id: patchManager
    }

}

