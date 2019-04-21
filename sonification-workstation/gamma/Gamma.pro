# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

#TARGET = Gamma

HEADERS = \
   $$PWD/external/include/portaudio.h \
   $$PWD/external/include/sndfile.h \
   $$PWD/Gamma/Access.h \
   $$PWD/Gamma/Allocator.h \
   $$PWD/Gamma/Analysis.h \
   $$PWD/Gamma/arr.h \
   $$PWD/Gamma/AudioIO.h \
   $$PWD/Gamma/Config.h \
   $$PWD/Gamma/Constants.h \
   $$PWD/Gamma/Containers.h \
   $$PWD/Gamma/Conversion.h \
   $$PWD/Gamma/Delay.h \
   $$PWD/Gamma/DFT.h \
   $$PWD/Gamma/Domain.h \
   $$PWD/Gamma/Effects.h \
   $$PWD/Gamma/Envelope.h \
   $$PWD/Gamma/FFT.h \
   $$PWD/Gamma/Filter.h \
   $$PWD/Gamma/FormantData.h \
   $$PWD/Gamma/Gamma.h \
   $$PWD/Gamma/gen.h \
   $$PWD/Gamma/HRFilter.h \
   $$PWD/Gamma/ipl.h \
   $$PWD/Gamma/mem.h \
   $$PWD/Gamma/Node.h \
   $$PWD/Gamma/Noise.h \
   $$PWD/Gamma/Oscillator.h \
   $$PWD/Gamma/Print.h \
   $$PWD/Gamma/pstdint.h \
   $$PWD/Gamma/Recorder.h \
   $$PWD/Gamma/rnd.h \
   $$PWD/Gamma/SamplePlayer.h \
   $$PWD/Gamma/Scheduler.h \
   $$PWD/Gamma/scl.h \
   $$PWD/Gamma/SoundFile.h \
   $$PWD/Gamma/Spatial.h \
   $$PWD/Gamma/Strategy.h \
   $$PWD/Gamma/Sync.h \
   $$PWD/Gamma/tbl.h \
   $$PWD/Gamma/Thread.h \
   $$PWD/Gamma/Timer.h \
   $$PWD/Gamma/TransferFunc.h \
   $$PWD/Gamma/Types.h \
   $$PWD/Gamma/UnitMaps.h \
   $$PWD/src/fftpack++.h \
   $$PWD/gamma.h

SOURCES = \
   $$PWD/external/lib_win64/libsndfile-1.lib \
   $$PWD/external/lib_win64/portaudio_x64.lib \
   $$PWD/src/arr.cpp \
   $$PWD/src/AudioIO.cpp \
   $$PWD/src/Conversion.cpp \
   $$PWD/src/DFT.cpp \
   $$PWD/src/Domain.cpp \
   $$PWD/src/FFT_fftpack.cpp \
   $$PWD/src/fftpack++1.cpp \
   $$PWD/src/fftpack++2.cpp \
   $$PWD/src/Print.cpp \
   $$PWD/src/Recorder.cpp \
   $$PWD/src/Scheduler.cpp \
   $$PWD/src/scl.cpp \
   $$PWD/src/SoundFile.cpp \
   $$PWD/src/Timer.cpp

INCLUDEPATH = \
    $$PWD/. \
    $$PWD/external/include \
    $$PWD/Gamma \
    $$PWD/src

#DEFINES = 

