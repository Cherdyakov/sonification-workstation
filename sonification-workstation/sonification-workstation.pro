TEMPLATE = subdirs
SUBDIRS = SonificationWorkstation Gamma

#SUBDIRS += \
#    sonification-workstation/SonificationWorkstation.pro \
#    gamma/Gamma.pro

Gamma.subdir = Gamma
SonificationWorkstation.subdir = SonificationWorkstation


SonificationWorkstation.depends = Gamma

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/gamma/release/ -lGamma
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/gamma/debug/ -lGamma
else:unix: LIBS += -L$$OUT_PWD/gamma/ -lGamma

INCLUDEPATH += $$PWD/gamma
DEPENDPATH += $$PWD/gamma
