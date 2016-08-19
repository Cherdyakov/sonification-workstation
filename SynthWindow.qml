import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.0

ApplicationWindow {

    id: synthWindow

    // holds every item in the workspace for iterating
    property var synthItems: [dac]
    // one of the synthItems in the workspace is in
    //the process of being connected
    property bool connecting: false

    width: 640
    height: 480
    visible: true
    title: qsTr("Sonification Workstation: Synthesis")

    menuBar: MenuBar {
        id: menuBar
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Exit")
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

        MouseArea {
            id: workspaceMouseArea
            hoverEnabled: true
            anchors.fill: workspace
            onMouseXChanged: if(connecting) { canvas.requestPaint() }
            onMouseYChanged: if(connecting) { canvas.requestPaint() }
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

        PatchManager {
            id: patchManager
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
                // clear canvas
                ctx.clearRect(0, 0, canvas.width, canvas.height)
                // setup the stroke
                ctx.lineWidth = 4
                ctx.strokeStyle = "chartreuse"

                // iterate through all synth items
                var count = patchManager.patches.length()
                //                console.log(count)
                for(var i = 0; i < count; i++)
                {
                    var patch = patchManager.patches[i]
                    var x1 = patch.xBegin
                    var y1 = patch.yBegin
                    var x2 = patch.xEnd
                    var y2 = patch.yEnd

                    // begin a new path to draw
                    ctx.beginPath()
                    // line start point
                    ctx.moveTo(x1,y1)
                    // line end point
                    ctx.lineTo(x2,y2)
                    // stroke using line width and stroke style
                    ctx.stroke()
                }
            }



        }
    }

}

