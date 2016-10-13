import QtQuick 2.7
import QtQuick.Controls 2.0
import "Style.js" as Style

SpinBox {
    id: spinbox
    editable: true
    from: 0
    value: 44000
    to: 100 * 20000
    stepSize: 1

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
