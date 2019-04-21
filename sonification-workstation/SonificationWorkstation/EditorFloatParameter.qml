import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.11
import "Style.js" as Style

Item {
    id: root

    width: childrenRect.width
    height: childrenRect.height

    property alias scaled: scaler.scaled
    property alias scaleLow: scaler.low
    property alias scaleRealLow: scaler.realLow
    property alias scaleHigh: scaler.high
    property alias scaleRealHigh: scaler.realHigh
    property alias scaleExp: scaler.exp
    property alias scaleRealExp: scaler.realExp
    property alias mapper: mapper
    property alias scaler: scaler

    ColumnLayout {
        id: layout

        EditorMapper {
            id: mapper
        }

        EditorScaler {
            id: scaler
        }
    }

}
