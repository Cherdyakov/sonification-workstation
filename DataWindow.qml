import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.0
import QtQuick.Window 2.0
import QtCharts 2.0

ApplicationWindow {

    width: 640
    height: 480
    visible: true
    title: qsTr("Sonification Workstation: Data")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Exit")
                onTriggered: quit()
            }
        }
    }

    TabView {
        id: tabs
        anchors.fill: parent

        Tab {
            title: qsTr("Table View")
            TableView {
                id: table
                anchors.fill: parent


            }
        }
        Tab {
            title: qsTr("Graphing View")
            ChartView {
                anchors.fill: parent
                theme: ChartView.ChartThemeBrownSand
                antialiasing: true

                PieSeries {
                    id: pieSeries
                    PieSlice { label: "eaten"; value: 94.9 }
                    PieSlice { label: "not yet eaten"; value: 5.1 }
                }
            }
        }
    }



    statusBar: StatusBar {
        id: statusBar
    }
}
