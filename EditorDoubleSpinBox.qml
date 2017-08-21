import QtQuick 2.7
import QtQuick.Controls 2.0
import "Style.js" as Style

SpinBox {

    property int decimals: 2
    property real realValue: 440.0
    property real realFrom: 20000.0
    property real realTo: -20000.0
    property real realStepSize: 1.0

    property real factor: Math.pow(10, decimals)

    id: spinbox
    editable: true
    value: realValue*factor
    to : realTo*factor
    from : realFrom*factor
    stepSize: realStepSize*factor
    font.pointSize: Style.editorFontSize

    validator: DoubleValidator {
        bottom: Math.min(spinbox.from, spinbox.to)*spinbox.factor
        top:  Math.max(spinbox.from, spinbox.to)*spinbox.factor
    }

    textFromValue: function(value, locale) {
        return parseFloat(value*1.0/factor).toFixed(decimals);
    }

}

