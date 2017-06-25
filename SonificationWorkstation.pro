QT += qml quick widgets charts printsupport

CONFIG += c++11

SOURCES += \
    mainwindow.cpp \
    main.cpp \
    oscillator.cpp \
    audifier.cpp \
    timerworker.cpp \
    filereader.cpp \
    ../../../CodeLibs/qcustomplot/qcustomplot.cpp \
    plotter.cpp \
    playhead.cpp \
    qtoscillator.cpp \
    qtsynthitem.cpp \
    qtaudifier.cpp \
    modulator.cpp \
    qtmodulator.cpp \
    transport.cpp \
    transportwidget.cpp \
    qttransport.cpp \
    utility.cpp \
    panner.cpp \
    qtpanner.cpp \
    envelope.cpp \
    qtenvelope.cpp \
    volume.cpp \
    qtvolume.cpp \
    noise.cpp \
    qtnoise.cpp

RESOURCES += qml.qrc

TEMPLATE = app

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    mainwindow.h \
    synthitem.h \
    callback.h \
    userdata.h \
    oscillator.h \
    ringbuffer.h \
    audifier.h \
    timerworker.h \
    filereader.h \
    ../../../CodeLibs/qcustomplot/qcustomplot.h \
    plotter.h \
    playhead.h \
    enums.h \
    qtoscillator.h \
    qtsynthitem.h \
    qtaudifier.h \
    modulator.h \
    qtmodulator.h \
    transport.h \
    transportwidget.h \
    qttransport.h \
    utility.h \
    frame.h \
    panner.h \
    qtpanner.h \
    envelope.h \
    qtenvelope.h \
    volume.h \
    qtvolume.h \
    noise.h \
    qtnoise.h

FORMS +=

#My MBP
# Gamma synthesis library
#LIBS += -L/Users/Sean/libs/Gamma-master/build/lib -lGamma
#INCLUDEPATH += /Users/Sean/libs/Gamma-master/Gamma
## RT Audio library
#LIBS += -L/Users/Sean/libs/rtaudio-4.1.2 -lrtaudio
#INCLUDEPATH += /Users/Sean/libs/rtaudio-4.1.2/include
## oscpack
##LIBS += -L/Users/Sean/libs/oscpack_1_1_0/oscpack/lib -loscpack
##INCLUDEPATH += /Users/Sean/libs/oscpack_1_1_0/oscpack/include
## Core Audio
#DEFINES += __MACOSX_CORE__
#INCLUDEPATH += /usr/local/include

#My Linux Desktop
# Gamma synthesis library
LIBS += -L/home/sean/CodeLibs/Gamma-master/build/lib -lGamma
INCLUDEPATH += /home/sean/CodeLibs/Gamma-master/Gamma
# RT Audio library
LIBS += -L/home/sean/CodeLibs/rtaudio-4.1.2 -lrtaudio
INCLUDEPATH += /home/sean/CodeLibs/rtaudio-4.1.2/include
# Secret Rabbit Code
LIBS += -L/home/sean/CodeLibs/libsamplerate-0.1.9 -lsamplerate
INCLUDEPATH += /home/sean/CodeLibs/libsamplerate-0.1.9
# qcustomplot
INCLUDEPATH += /home/sean/CodeLibs/qcustomplot

DISTFILES +=
