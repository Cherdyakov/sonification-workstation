QT += qml quick widgets charts

CONFIG += c++11

SOURCES += \
    mainwindow.cpp \
    main.cpp \
    synthitem.cpp \
    synthgraph.cpp \
    output.cpp \
    oscillator.cpp \
    tablemodel.cpp \
    synthwindow.cpp \
    csvreader.cpp \
    horizontalproxymodel.cpp \
    scatterview.cpp \
    lineview.cpp \
    ringbuffer.cpp \
    sequencer.cpp

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
    synthgraph.h \
    userdata.h \
    output.h \
    oscillator.h \
    tablemodel.h \
    synthwindow.h \
    csvreader.h \
    horizontalproxymodel.h \
    scatterview.h \
    lineview.h \
    ringbuffer.h \
    sequencer.h

FORMS += \
    synthwindow.ui

##My MBP
## Gamma synthesis library
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
LIBS += -L/home/sean/lCodeLibsibs/rtaudio-4.1.2 -lrtaudio
INCLUDEPATH += /home/sean/CodeLibs/rtaudio-4.1.2/include

DISTFILES +=
