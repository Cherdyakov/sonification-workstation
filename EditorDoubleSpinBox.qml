import QtQuick 2.7
import QtQuick.Controls 2.0
import "Style.js" as Style

SpinBox {

    property int decimals: 2
    property real doubleValue: 440.0
    property real doubleFrom: -20000.0
    property real doubleTo: 20000.0
    property real doubleStepSize: 1.0

    property real factor: Math.pow(10, decimals)

    id: spinBox
    onValueChanged: {
        doubleValue = value / factor
    }

    editable: true
    value: doubleValue*factor
    to: doubleTo*factor
    from : doubleFrom*factor
    stepSize: doubleStepSize*factor
    font.pointSize: Style.editorFontSize

    validator: DoubleValidator {
        bottom: Math.min(spinBox.from, spinBox.to)*spinBox.factor
        top:  Math.max(spinBox.from, spinBox.to)*spinBox.factor
    }

    valueFromText: function(text, locale) {
        return Number.fromLocaleString(locale, text) * factor
    }

    textFromValue: function(value, locale) {
        return parseFloat(value * 1.0 / factor).toFixed(decimals)
    }

}


