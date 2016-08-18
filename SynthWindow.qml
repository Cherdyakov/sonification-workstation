import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.0

ApplicationWindow {

    id: synthWindow

    property var synthItems: [dac]

    width: 640
    height: 480
    visible: true
    title: qsTr("Sonification Workstation: Synthesis")

    menuBar: MenuBar {
        id: menuBar
        Menu {
            title: "File"
            MenuItem {
                text: "Exit"
                onTriggered:  {
                    quit()
                    console.log("click")
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
                    componentFile: "OscillatorGUI.qml"
                    source: "images/oscIcon.png"
                    image: "images/oscIcon.png"
                }
            }
        }


        //this scroll area is the workspace where
        //synthItems are dropped and built into the
        //synthesis graph
        ScrollView {
            id: workspace

            anchors {
                top: toolbox.bottom
                left: parent.left
                right: parent.right
                bottom: parent.bottom
            }

            DropArea {
                anchors.fill: parent
            }

        }

        OutGUI {
            id: dac
            z: 100
            created: true
            anchors {
                horizontalCenter: parent.horizontalCenter
                bottom: parent.bottom
                bottomMargin: 8
            }


        }

        //canvas on which the connections are drawn
        Canvas {
            id: canvas
            z: 0

            anchors {
                top: workspace.top
                bottom: workspace.bottom
                left: workspace.left
                right: workspace.right
            }

            onPaint: {


                // get context to draw with
                var ctx = getContext("2d")
                //clear canvas
                ctx.clearRect(0, 0, canvas.width, canvas.height)
                // setup the stroke
                ctx.lineWidth = 4
                ctx.strokeStyle = "blue"

                //iterate through all synth items
                var count = synthItems.length
                for(var i = 0; i < count; i++)
                {
                    var parent = synthItems[i]
                    //and draw connections from each parent to their children
                    var childCount = parent.children.length
                    for(var j = 0; j < childCount; j++)
                    {
                        var child = parent.children[j]
                        // begin a new path to draw
                        ctx.beginPath()
                        // line start point
                        var cord = parent.mapToItem(workspace, 0, 0)
                        ctx.moveTo((cord.x + parent.width / 2), (cord.y + parent.height / 2))
                        // line end point
                        cord = child.mapToItem(workspace, 0, 0)
                        ctx.lineTo((cord.x + child.width / 2), (cord.y + child.height / 2))
                        // stroke using line width and stroke style
                        ctx.stroke()
                    }
                }



            }
        }

    }


}
