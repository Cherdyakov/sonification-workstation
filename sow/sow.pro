TEMPLATE = subdirs

#SUBDIRS += \
#    sonification-workstation/SonificationWorkstation.pro \
#    gamma/Gamma.pro

gamma_lib.subdir = gamma
son_workstation.subdir = sonification-workstation

SUBDIRS = gamma_lib son_workstation

son_workstation.depends = gamma_lib



win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/gamma/release/ -lGamma
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/gamma/debug/ -lGamma
else:unix: LIBS += -L$$OUT_PWD/gamma/ -lGamma

INCLUDEPATH += $$PWD/gamma
DEPENDPATH += $$PWD/gamma
