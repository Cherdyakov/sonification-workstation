# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

#TARGET = SonificationWorkstation

TEMPLATE = app
CONFIG += c++17
RESOURCES += qml.qrc \
            styles.qrc

# Default rules for deployment
include(deployment.pri)

HEADERS = \
   $$PWD/external/exprtk/exprtk.hpp \
   $$PWD/external/qcustomplot/qcustomplot.h \
   $$PWD/amod.h \
   $$PWD/audifier.h \
   $$PWD/callback.h \
   $$PWD/commands.h \
   $$PWD/constants.h \
   $$PWD/dataprocessor.h \
   $$PWD/dataset.h \
   $$PWD/enums.h \
   $$PWD/envelope.h \
   $$PWD/equalizer.h \
   $$PWD/filereader.h \
   $$PWD/fmod.h \
   $$PWD/frame.h \
   $$PWD/granulator.h \
   $$PWD/mainwindow.h \
   $$PWD/mapevaluator.h \
   $$PWD/noise.h \
   $$PWD/oscillator.h \
   $$PWD/panner.h \
   $$PWD/parameter.h \
   $$PWD/parameterfloat.h \
   $$PWD/parameterfloatinterface.h \
   $$PWD/parameterindex.h \
   $$PWD/parameterindexinterface.h \
   $$PWD/playhead.h \
   $$PWD/ringbuffer.h \
   $$PWD/style.h \
   $$PWD/synthitem.h \
   $$PWD/track.h \
   $$PWD/trackheader.h \
   $$PWD/trackname.h \
   $$PWD/trackplotter.h \
   $$PWD/trackview.h \
   $$PWD/transport.h \
   $$PWD/transportwidget.h \
   $$PWD/userdata.h \
   $$PWD/utility.h \
   $$PWD/volume.h

SOURCES = \
   $$PWD/external/qcustomplot/qcustomplot.cpp \
   $$PWD/images/alpha.png \
   $$PWD/images/AM.png \
   $$PWD/images/AUD.png \
   $$PWD/images/down-arrow.svg \
   $$PWD/images/ENV.png \
   $$PWD/images/EQ.png \
   $$PWD/images/FM.png \
   $$PWD/images/interpolate-off.svg \
   $$PWD/images/interpolate-on.svg \
   $$PWD/images/logo.png \
   $$PWD/images/logo.svg \
   $$PWD/images/loop-off.svg \
   $$PWD/images/loop-on.svg \
   $$PWD/images/MOD.png \
   $$PWD/images/NSE.png \
   $$PWD/images/OSC.png \
   $$PWD/images/OUT.png \
   $$PWD/images/PAN.png \
   $$PWD/images/pause.svg \
   $$PWD/images/play.svg \
   $$PWD/images/up-arrow.svg \
   $$PWD/images/VOL.png \
   $$PWD/AM.qml \
   $$PWD/amod.cpp \
   $$PWD/AUD.qml \
   $$PWD/audifier.cpp \
   $$PWD/dataprocessor.cpp \
   $$PWD/dataset.cpp \
   $$PWD/deployment.pri \
   $$PWD/Editor.qml \
   $$PWD/EditorDoubleSpinBox.qml \
   $$PWD/EditorFixed.qml \
   $$PWD/EditorFloatParameter.qml \
   $$PWD/EditorLabel.qml \
   $$PWD/EditorLayout.qml \
   $$PWD/EditorMapper.qml \
   $$PWD/EditorMenu.qml \
   $$PWD/EditorParameterHeader.qml \
   $$PWD/EditorScaler.qml \
   $$PWD/EditorTitle.qml \
   $$PWD/ENV.qml \
   $$PWD/envelope.cpp \
   $$PWD/EQ.qml \
   $$PWD/equalizer.cpp \
   $$PWD/filereader.cpp \
   $$PWD/FM.qml \
   $$PWD/fmod.cpp \
   $$PWD/granulator.cpp \
   $$PWD/ItemCreation.js \
   $$PWD/main.cpp \
   $$PWD/main.qml \
   $$PWD/mainwindow.cpp \
   $$PWD/noise.cpp \
   $$PWD/NSE.qml \
   $$PWD/OSC.qml \
   $$PWD/oscillator.cpp \
   $$PWD/OUT.qml \
   $$PWD/Palette.qml \
   $$PWD/PaletteItem.qml \
   $$PWD/PAN.qml \
   $$PWD/panner.cpp \
   $$PWD/parameter.cpp \
   $$PWD/parameterfloat.cpp \
   $$PWD/parameterfloatinterface.cpp \
   $$PWD/parameterindex.cpp \
   $$PWD/parameterindexinterface.cpp \
   $$PWD/PatchManager.qml \
   $$PWD/playhead.cpp \
   $$PWD/qml.qrc \
   $$PWD/README.md \
   $$PWD/SessionCode.js \
   $$PWD/Style.js \
   $$PWD/styles.qrc \
   $$PWD/styles.qss \
   $$PWD/synthitem.cpp \
   $$PWD/SynthItem.qml \
   $$PWD/track.cpp \
   $$PWD/trackheader.cpp \
   $$PWD/trackname.cpp \
   $$PWD/trackplotter.cpp \
   $$PWD/trackview.cpp \
   $$PWD/transport.cpp \
   $$PWD/transportwidget.cpp \
   $$PWD/utility.cpp \
   $$PWD/Utils.js \
   $$PWD/VOL.qml \
   $$PWD/volume.cpp

INCLUDEPATH = \
    $$PWD/. \
    $$PWD/external/qcustomplot

#DEFINES = 

