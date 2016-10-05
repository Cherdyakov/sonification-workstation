import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.0

ApplicationWindow {

    id: synthWindow

    // holds every item in the workspace for iterating
    property var synthItems: []
    //canvas for drawing connections
    property alias canvas: canvas
    property alias workspace: workspace

    width: 800
    height: 600
    visible: true
    title: qsTr("Sonification Workstation: Synthesis")

    Component.onCompleted: {
    }

    menuBar: MenuBar {
        id: menuBar
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Exit")
                onTriggered:  {
                    quit()
                    //                    console.log("click")
                }

            }
        }
    }

    statusBar: StatusBar {
        id: statusBar
    }

    Item {
        id: window
        anchors.fill: parent

        // top panel
        Rectangle {
            id: toolbox

            height: 70
            color: "gray"
            anchors { right: parent.right; top: parent.top; left: parent.left}

            Row {
                id: palette
                anchors.centerIn: parent
                spacing: 8

                PaletteItem {
                    anchors.verticalCenter: parent.verticalCenter
                    componentFile: "OSC.qml"
                    source: "images/oscIcon.png"
                    image: "images/oscIcon.png"
                }
            }
        }

        SplitView {

            orientation: Qt.Vertical

            anchors {
                top: toolbox.bottom
                left: window.left
                right: window.right
                bottom: window.bottom
            }

            ScrollView {
                id: workspaceScroll
                clip: true
                z: 0
//                color: "yellow"
                Layout.fillWidth: true
                Layout.fillHeight: true
                flickableItem.contentHeight: workspace.height
                flickableItem.contentWidth: workspace.width


                Rectangle {
                    id: workspace

                    Layout.minimumWidth: 100
                    width: childrenRect.width + 20
                    height: childrenRect.height + 20
                    color: "yellow"

                MouseArea {
                    id: workspaceMouseArea
                    hoverEnabled: true
                    anchors.fill: parent
                    onMouseXChanged: if(patchManager.patchBegin) { canvas.requestPaint() }
                    onMouseYChanged: if(patchManager.patchBegin) { canvas.requestPaint() }
                }

                //canvas on which the connections are drawn
                Canvas {
                    id: canvas
                    z: 0

                    anchors.fill: parent

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

                                    var startPoint = mapFromItem(workspace, parentItem.x, parentItem.y)
                                    var beginX = startPoint.x + parentItem.width / 2
                                    var beginY = startPoint.y + parentItem.height / 2
                                    //                    console.log(patch.startPoint)
                                    //                            console.log(child)
                                    var endPoint = mapFromItem(workspace, childItem.x, childItem.y)
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
                                startPoint = mapFromItem(workspace, beginning.x, beginning.y)
                                beginX = startPoint.x + beginning.width / 2
                                beginY = startPoint.y + beginning.height / 2

                                endPoint = mapToItem(canvas, workspaceMouseArea.mouseX, workspaceMouseArea.mouseY )
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

                OUT {
                    id: dac
                    created: true
                    z: 200
                    anchors {
                        horizontalCenter: parent.horizontalCenter
                        bottom: parent.bottom
                        bottomMargin: 8
                    }
                }
                }

            }

            ScrollView {
                id: editorScroll
                width: 300//parent.width / 3
                Layout.minimumWidth: 100
                Layout.fillHeight: true

            }

        }

        PatchManager {
            id: patchManager
        }

    }
}

