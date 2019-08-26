QT += qml quick widgets printsupport

RESOURCES += qml.qrc \
    styles.qrc

TEMPLATE = app

TARGET = "Sonification Workstation"

CONFIG += c++17

QTPLUGIN += qtaccessiblewidgets

# Application icons
win32: RC_ICONS = sow.ico
macx: ICON = sow.icns

# For large object files in MSVCC
win32: QMAKE_CXXFLAGS += -bigobj

# Default rules for deployment
!include(deployment.pri) {
    error("deployment.pri not found")
}
# Common includes
!include(../common.pri) {
    error("common.pri not found")
}

HEADERS = \
   $$PWD/external/exprtk/exprtk.hpp \
   $$PWD/external/qcustomplot/qcustomplot.h \
   $$PWD/amod.h \
   $$PWD/audifier.h \
   $$PWD/callback.h \
   $$PWD/commands.h \
   $$PWD/constants.h \
#   $$PWD/dataprocessor.h \
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
   $$PWD/volume.h \
    aboutmessage.h \
    datasetimportdialog.h \
    mastervolumeslider.h \
    recorder.h \
    thememanager.h

SOURCES = \
   $$PWD/external/qcustomplot/qcustomplot.cpp \
   $$PWD/amod.cpp \
   $$PWD/audifier.cpp \
#   $$PWD/dataprocessor.cpp \
   $$PWD/dataset.cpp \
   $$PWD/envelope.cpp \
   $$PWD/equalizer.cpp \
   $$PWD/filereader.cpp \
   $$PWD/fmod.cpp \
   $$PWD/granulator.cpp \
   $$PWD/main.cpp \
   $$PWD/mainwindow.cpp \
   $$PWD/noise.cpp \
   $$PWD/oscillator.cpp \
   $$PWD/panner.cpp \
   $$PWD/parameter.cpp \
   $$PWD/parameterfloat.cpp \
   $$PWD/parameterfloatinterface.cpp \
   $$PWD/parameterindex.cpp \
   $$PWD/parameterindexinterface.cpp \
   $$PWD/playhead.cpp \
   $$PWD/synthitem.cpp \
   $$PWD/track.cpp \
   $$PWD/trackheader.cpp \
   $$PWD/trackname.cpp \
   $$PWD/trackplotter.cpp \
   $$PWD/trackview.cpp \
   $$PWD/transport.cpp \
   $$PWD/transportwidget.cpp \
   $$PWD/utility.cpp \
   $$PWD/volume.cpp \
    aboutmessage.cpp \
    datasetimportdialog.cpp \
    mastervolumeslider.cpp \
    recorder.cpp \
    thememanager.cpp

INCLUDEPATH = \
    $$PWD/. \
    $$PWD/external/qcustomplot

# Gamma
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Gamma/release/ -lGamma
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Gamma/debug/ -lGamma
else:unix: LIBS += -L$$OUT_PWD/../Gamma/ -lGamma

INCLUDEPATH += $$PWD/../Gamma
DEPENDPATH += $$PWD/../Gamma

# PortAudio (required for Gamma)
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Gamma/external/lib_win64/ -lportaudio_x64
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Gamma/external/lib_win64/ -lportaudio_x64
else:unix:!macx: LIBS += -lportaudio
else:macx: LIBS += -L$$PWD/../Gamma/external/lib_osx/ -lportaudio.2

INCLUDEPATH += $$PWD/../Gamma/external/lib_win64
DEPENDPATH += $$PWD/../Gamma/external/lib_win64
INCLUDEPATH += $$PWD/../Gamma/external/lib_osx
DEPENDPATH += $$PWD/../Gamma/external/lib_osx

# LibSndFile (required for Gamma)
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Gamma/external/lib_win64/ -llibsndfile-1
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Gamma/external/lib_win64/ -llibsndfile-1
else:unix:!macx: LIBS += -llibsndfile-1
else:macx: LIBS += -L$$PWD/../Gamma/external/lib_osx/ -llibsndfile-1

DISTFILES += \
    sow.ico
