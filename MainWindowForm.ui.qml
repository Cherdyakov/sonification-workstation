import QtQuick 2.4
import QtQuick.Controls 2.0

Item {
    width: 400
    height: 400

    Rectangle {
        id: workSpaceRect
        color: "#ffffff"

        anchors {
            top: parent.top
            bottom: bottomToolBar.top
            left: parent.left
            right: synthItemsToolBar.left
        }
    }

    ToolBar {
        id: bottomToolBar

        height: 40
        width: parent.width

        anchors {
            bottom: parent.bottom
        }


    }

    ToolBar {
        id: synthItemsToolBar
        width: 80
        height: parent.height

        anchors {
            top: parent.top
            bottom: bottomToolBar.top
            right: parent.right
        }
    }
}
