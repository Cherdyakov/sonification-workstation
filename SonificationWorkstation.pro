QT += qml quick

CONFIG += c++11

SOURCES += main.cpp \
    synthitem.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    synthitem.h \
    callback.h

# Gamma synthesis library
LIBS += -L/home/sean/libs/Gamma-master/build/lib -lGamma
INCLUDEPATH += /home/sean/libs/Gamma-master/Gamma
# RT Audio library
LIBS += -L/home/sean/libs/rtaudio-4.1.2 -lrtaudio
INCLUDEPATH += /home/sean/libs/rtaudio-4.1.2/include
