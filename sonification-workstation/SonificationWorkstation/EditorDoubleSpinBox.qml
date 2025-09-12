import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "Style.js" as Style

SpinBox {
    id: spinbox
    from: 0
    value: 110
    to: 20000 * 100
    stepSize: 100
    editable: true
    font.pointSize: Style.editorFontSize
    Layout.maximumHeight: Style.editorRowHeight + 2
    padding: 0

    property int decimals: 2
    property real realValue: value / 100

    up.indicator.implicitWidth: 16
    down.indicator.implicitWidth: 16

    contentItem: TextInput {
        z: 2
        text: spinbox.textFromValue(spinbox.value, spinbox.locale)
        font.pointSize: Style.editorFontSize
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter
    }

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


