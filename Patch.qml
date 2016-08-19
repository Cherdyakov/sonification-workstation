import QtQuick 2.0

Item {
    id: root

    property double xBegin: 100
    property double yBegin: 100
    property double xEnd: 300
    property double yEnd: 300
    property string anchorColor
    property PatchPoint patchBegin
    property PatchPoint patchEnd


    Rectangle {
        id: anchor
        height: 12
        width: 12
        color: anchorColor
    }
}
