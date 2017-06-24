import QtQuick 2.7
import SonLib 1.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0
import "Style.js" as Style

SynthItem {
    id: root
    label: qsTr("VOL")
    type: QtTransport.VOLUME
    childType: QtSynthItem.INPUT
    mainColor: Style.volColor
    textColor: Style.itemTextColor

    Editor {

        id: editor
        property bool useFixedVolume: true
        property double fixedVolume: 1
        property bool useVolumeScaling: true
        property double volumeScaleLow: 0
        property double volumeScaleHigh: 1
        property double volumeScaleExp: 1

        Component.onCompleted: {
            volumeEditor.spinBox.value = fixedVolume * 100
            fixedEditor.checkBox.checked = useFixedVolume
            volumeScaler.lowSpinBox.value = volumeScaleLow * 100
            volumeScaler.highSpinBox.value = volumeScaleHigh * 100
            volumeScaler.expSpinBox.value = volumeScaleExp * 100
            volumeScaler.checkBox.checked = useVolumeScaling
        }

        onUseFixedVolumeChanged: {
            implementation.setVolumeFixed(useFixedVolume)
        }

        onFixedVolumeChanged: {
            implementation.setVolume(fixedVolume)
        }

        EditorLayout {
            id: layout
            title: label

            RowLayout {

                EditorDoubleParam {
                    id: volumeEditor
                    spinBox.from: 0
                    spinBox.to: 100
                    spinBox.stepSize: 1
                    onParamValueChanged: {
                        if (editor.fixedVolume !== value) {
                            editor.fixedVolume = value
                        }
                    }
                }

                EditorFixedParam {
                    id: fixedEditor
                    label.text: qsTr("Fixed: ")
                    onFixedChanged: {
                        if (editor.useFixedVolume != fixed) {
                            editor.useFixedVolume = fixed
                        }
                    }
                }

            }

            EditorMapper {
                id: volumeMapper
                label.text: qsTr("Volume Source: ")
                maxIndexes: 128
                onMappingsChanged:
                {
                    if(root.mappedRows !== mappings) {
                        root.mappedRows = mappings
                        var implementationMappings = mappings.map( function(value) {
                            return value - 1;
                        } )
                        implementation.setVolumeIndexes(implementationMappings)
                    }
                }
            }

            EditorScaler {
                id: volumeScaler
                label.text: qsTr("Volume Scaling: ")
                lowLabel.text: qsTr("Volume Low: ")
                highLabel.text: qsTr("Volume High: ")
                lowSpinBox.from: 0
                lowSpinBox.to: 100
                lowSpinBox.stepSize: 1
                highSpinBox.from: -100
                highSpinBox.to: 100
                highSpinBox.stepSize: 1

                onLowChanged:
                {
                    if(editor.volumeScaleLow !== low) {
                        editor.volumeScaleLow = low
                        implementation.setVolumeScaleVals(editor.volumeScaleLow,
                                                          editor.volumeScaleHigh,
                                                          editor.volumeScaleExp)
                    }
                }
                onHighChanged:
                {
                    if(editor.volumeScaleHigh !== high) {
                        editor.volumeScaleHigh = high
                        implementation.setVolumeScaleVals(editor.volumeScaleLow,
                                                          editor.volumeScaleHigh,
                                                          editor.volumeScaleExp)                    }
                }
                onExponentChanged:
                {
                    if(editor.volumeScaleExp !== exp) {
                        editor.volumeScaleExp = exp
                        implementation.setVolumeScaleVals(editor.volumeScaleLow,
                                                          editor.volumeScaleHigh,
                                                          editor.volumeScaleExp)                    }
                }
                onUseScalingChanged:
                {
                    if(editor.useVolumeScaling !== scaling) {
                        editor.useVolumeScaling = scaling
                        implementation.setVolumeScaled(editor.useVolumeScaling)
                    }
                }
            }
        }
    }

}


