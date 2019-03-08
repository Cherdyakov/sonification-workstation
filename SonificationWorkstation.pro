QT += qml quick widgets printsupport
RESOURCES += qml.qrc
TEMPLATE = app
CONFIG += c++11
# Default rules for deployment.
include(deployment.pri)

SOURCES += \
    mainwindow.cpp \
    main.cpp \
    oscillator.cpp \
#    audifier.cpp \
    timerworker.cpp \
    filereader.cpp \
    external/qcustomplot/qcustomplot.cpp \
    plotter.cpp \
    playhead.cpp \
    qtoscillator.cpp \
    qtsynthitem.cpp \
#    qtaudifier.cpp \
#    modulator.cpp \
#    qtmodulator.cpp \
    transport.cpp \
    transportwidget.cpp \
    qttransport.cpp \
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
    qtutility.cpp \
    trackview.cpp \
    track.cpp \
    trackheader.cpp \
    trackplotter.cpp \
    trackname.cpp \
    dataprocessor.cpp

HEADERS += \
    mainwindow.h \
    synthitem.h \
    callback.h \
    userdata.h \
    oscillator.h \
    ringbuffer.h \
#    audifier.h \
    timerworker.h \
    filereader.h \
    external/qcustomplot/qcustomplot.h \
    plotter.h \
    playhead.h \
    qtoscillator.h \
    qtsynthitem.h \
#    qtaudifier.h \
#    modulator.h \
#    qtmodulator.h \
    transport.h \
    transportwidget.h \
    qttransport.h \
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
    qtutility.h \
    trackview.h \
    track.h \
    trackheader.h \
    trackplotter.h \
    trackname.h \
    dataprocessor.h \
    dataset.h

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
