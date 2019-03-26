QT += qml quick widgets printsupport
RESOURCES += qml.qrc
TEMPLATE = app
CONFIG += c++17
# Default rules for deployment.
include(deployment.pri)

SOURCES += \
    mainwindow.cpp \
    main.cpp \
#    oscillator.cpp \
#    audifier.cpp \
    timerworker.cpp \
    filereader.cpp \
    external/qcustomplot/qcustomplot.cpp \
    playhead.cpp \
#    qtaudifier.cpp \
#    modulator.cpp \
#    qtmodulator.cpp \
#    transport.cpp \
    transportwidget.cpp \
    utility.cpp \
#    panner.cpp \
#    qtpanner.cpp \
#    envelope.cpp \
#    qtenvelope.cpp \
#    volume.cpp \
#    qtvolume.cpp \
#    noise.cpp \
#    qtnoise.cpp \
#    equalizer.cpp \
#    qtequalizer.cpp \
#    granulator.cpp \
    session.cpp \
    trackview.cpp \
    track.cpp \
    trackheader.cpp \
    trackplotter.cpp \
    trackname.cpp \
    dataprocessor.cpp \
    dataset.cpp \
    synthitem.cpp \
    transport.cpp \
    oscillator.cpp \
    amod.cpp \
    fmod.cpp \
    audifier.cpp \
    panner.cpp \
    volume.cpp \
    envelope.cpp \
    noise.cpp \
    parameterfloat.cpp \
    parameterfloatinterface.cpp \
    parameter.cpp

HEADERS += \
    mainwindow.h \
#    synthitem.h \
    callback.h \
    userdata.h \
#    oscillator.h \
    ringbuffer.h \
#    audifier.h \
    timerworker.h \
    filereader.h \
    external/qcustomplot/qcustomplot.h \
    playhead.h \
#    qtaudifier.h \
#    modulator.h \
#    qtmodulator.h \
#    transport.h \
    transportwidget.h \
    utility.h \
    frame.h \
#    panner.h \
#    qtpanner.h \
#    envelope.h \
#    qtenvelope.h \
#    volume.h \
#    qtvolume.h \
#    noise.h \
#    qtnoise.h \
#    equalizer.h \
#    qtequalizer.h \
#    granulator.h \
    session.h \
    trackview.h \
    track.h \
    trackheader.h \
    trackplotter.h \
    trackname.h \
    dataprocessor.h \
    dataset.h \
    commands.h \
    enums.h \
    external/exprtk/exprtk.hpp \
    mapevaluator.h \
    synthitem.h \
    transport.h \
    oscillator.h \
    amod.h \
    fmod.h \
    audifier.h \
    constants.h \
    panner.h \
    volume.h \
    envelope.h \
    noise.h \
    parameterfloat.h \
    parameterfloatinterface.h \
    parameter.h

#Sean Ubuntu
BASEPATH = /home/sean/Documents/src
#Andres
#BASEPATH = /home/andres/Documents/src
# Gamma synthesis library
LIBS += -L$${BASEPATH}/Gamma-master/build/lib -L$${BASEPATH}/Gamma/build/lib -lGamma
INCLUDEPATH += $${BASEPATH}/Gamma-master
# qcustomplot
INCLUDEPATH +=  external/qcustomplot
# PortAudio
unix|win32: LIBS += -lportaudio

# Update qrc files
update_qml.target = qml.qrc
update_qml.commands = echo>>$${update_qml.target} # same as touch
update_qml.depends = $$files(path/to/resource/files/*, true) # recurse into subdirs
QMAKE_EXTRA_TARGETS += update_qml
PRE_TARGETDEPS += $${update_qml.target}
