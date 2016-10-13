import QtQuick 2.7
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0

Item  {
    id: root
    property alias radius: rect.radius
    property alias color: rect.color

    opacity: 0

    Rectangle {
        id: rect
        anchors.fill: parent
        height: parent.height
        width: parent.width
        radius: radius
    }

}
