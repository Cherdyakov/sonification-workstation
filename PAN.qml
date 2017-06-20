import QtQuick 2.7
import SonLib 1.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0
import "Style.js" as Style

SynthItem {
    id: root
    label: qsTr("PAN")
    type: QtTransport.PANNER
    childType: QtSynthItem.INPUT
    mainColor: Style.panColor
    textColor: Style.itemTextColor

    Editor {

        id: editor
        property bool useFixedPan: true
        property double fixedPan: 0
        property bool usePanScaling: true
        property double panScaleLow: -1
        property double panScaleHigh: 1
        property double panScaleExp: 1

        Component.onCompleted: {
            panEditor.spinBox.value = fixedPan * 100
            fixedEditor.checkBox.checked = useFixedPan
            panScaler.lowSpinBox.value = panScaleLow * 100
            panScaler.highSpinBox.value = panScaleHigh * 100
            panScaler.expSpinBox.value = panScaleExp * 100
            panScaler.checkBox.checked = usePanScaling
        }

        onUseFixedPanChanged: {
            implementation.setPanFixed(useFixedPan)
        }

        onFixedPanChanged: {
            implementation.setPan(fixedPan)
        }

        EditorLayout {
            id: layout
            title: label

            RowLayout {

                EditorDoubleParam {
                    id: panEditor
                    spinBox.from: -100
                    spinBox.to: 100
                    spinBox.stepSize: 1
                    onParamValueChanged: {
                        if (editor.fixedPan !== value) {
                            editor.fixedPan = value
                        }
                    }
                }

                EditorFixedParam {
                    id: fixedEditor
                    label.text: qsTr("Fixed: ")
                    onFixedChanged: {
                        if (editor.useFixedPan != fixed) {
                            editor.useFixedPan = fixed
                        }
                    }
                }

            }

            EditorMapper {
                id: panMapper
                label.text: qsTr("Pan Source: ")
                maxIndexes: 128
                onMappingsChanged:
                {
                    if(root.mappedRows !== mappings) {
                        root.mappedRows = mappings
                        var implementationMappings = mappings.map( function(value) {
                            return value - 1;
                        } )
                        implementation.setPanIndexes(implementationMappings)
                    }
                }
            }

            EditorScaler {
                id: panScaler
                label.text: qsTr("Pan Scaling: ")
                lowLabel.text: qsTr("Pan Low: ")
                highLabel.text: qsTr("Pan High: ")
                lowSpinBox.from: -100
                lowSpinBox.to: 100
                lowSpinBox.stepSize: 1
                highSpinBox.from: -100
                highSpinBox.to: 100
                highSpinBox.stepSize: 1

                onLowChanged:
                {
                    if(editor.panScaleLow !== low) {
                        editor.panScaleLow = low
                        implementation.setPanScaleVals(editor.panScaleLow,
                                                          editor.panScaleHigh,
                                                          editor.panScaleExp)
                    }
                }
                onHighChanged:
                {
                    if(editor.panScaleHigh !== high) {
                        editor.panScaleHigh = high
                        implementation.setPanScaleVals(editor.panScaleLow,
                                                          editor.panScaleHigh,
                                                          editor.panScaleExp)                    }
                }
                onExponentChanged:
                {
                    if(editor.panScaleExp !== exp) {
                        editor.panScaleExp = exp
                        implementation.setPanScaleVals(editor.panScaleLow,
                                                          editor.panScaleHigh,
                                                          editor.panScaleExp)                    }
                }
                onUseScalingChanged:
                {
                    if(editor.usePanScaling !== scaling) {
                        editor.usePanScaling = scaling
                        implementation.setPanScaled(editor.usePanScaling)
                    }
                }
            }
        }
    }

}


