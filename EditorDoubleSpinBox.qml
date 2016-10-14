import QtQuick 2.7
import QtQuick.Controls 2.0
import "Style.js" as Style

SpinBox {
    id: spinbox
//    value: 44000
    editable: true
    from: -2000000
    to: 2000000
    stepSize: 100
    font.pointSize: Style.editorFontSize

    property int decimals: 2
    property real realValue: value / 100

    validator: DoubleValidator {
        bottom: Math.min(spinbox.from, spinbox.to)
        top:  Math.max(spinbox.from, spinbox.to)
    }

    textFromValue: function(value, locale) {
        return Number(value / 100).toLocaleString(locale, 'f', spinbox.decimals)
    }

    valueFromText: function(text, locale) {
        return Number.fromLocaleString(locale, text) * 100
    }

}
