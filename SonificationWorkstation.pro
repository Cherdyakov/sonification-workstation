QT += qml quick widgets printsupport
RESOURCES += qml.qrc
TEMPLATE = app
CONFIG += c++17
# Default rules for deployment.
include(deployment.pri)

SOURCES += \
    mainwindow.cpp \
    main.cpp \
    filereader.cpp \
    external/qcustomplot/qcustomplot.cpp \
    playhead.cpp \
    transportwidget.cpp \
    utility.cpp \
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
    parameter.cpp \
    parameterindex.cpp \
    parameterindexinterface.cpp \
    equalizer.cpp

HEADERS += \
    mainwindow.h \
    callback.h \
    userdata.h \
    ringbuffer.h \
    filereader.h \
    external/qcustomplot/qcustomplot.h \
    playhead.h \
    transportwidget.h \
    utility.h \
    frame.h \
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
    parameter.h \
    parameterindex.h \
    parameterindexinterface.h \
    equalizer.h

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
