#include <QApplication>
#include <QDebug>
#include <QThread>
#include <QQmlContext>

#include "qtsynthitem.h"
#include "mainwindow.h"
#include "portaudio.h"
#include "callback.h"
#include "qttransport.h"
#include "ringbuffer.h"
#include "filereader.h"
#include "Gamma/Sync.h"

#define SR 44100
#define BLOCK_SIZE 512

void PrintAudioError(PaError e) {
    qDebug("PortAudio error: %s\n", Pa_GetErrorText(e));
}

using namespace sow;

int main(int argc, char *argv[])
{

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    qmlRegisterType<QtSynthItem>("SonLib", 1, 0, "QtSynthItem");
    qmlRegisterType<QtOscillator>("SonLib", 1, 0, "QtOscillator");
    qmlRegisterType<QtTransport>("SonLib", 1, 0, "QtTransport");
    qmlRegisterType<ParameterInterface>("SonLib", 1, 0, "SowParameter");
    qmlRegisterType<MainWindow>("MainWindow", 1, 0, "MainWindow");
    qmlRegisterType<SowEnums>("SowEnums", 0, 1, "SowEnums");
    qRegisterMetaType<SowEnums::ITEM>();
    qRegisterMetaType<SowEnums::PARAMETER>();

    MainWindow main_window;
    UserData uData;
    uData.root =  main_window.getTransport();

    main_window.show();

    //initialize Gamma
    gam::Sync::master().spu(SR);

    PaStream *stream;
    PaError err;

    err = Pa_Initialize();
    if(err != paNoError) PrintAudioError(err);

    // Open an audio I/O stream
    err = Pa_OpenDefaultStream( &stream,
                                0,
                                2,
                                paFloat32,
                                SR,
                                BLOCK_SIZE,
                                callback,
                                &uData );

    if(err != paNoError) PrintAudioError(err);

    err = Pa_StartStream( stream );
    if(err != paNoError) PrintAudioError(err);

    // Place cleanup code after a.exec, before returning exit code
    const int ret = a.exec();

    // Cleanup PortAudio
    err = Pa_AbortStream( stream );
    if(err != paNoError) PrintAudioError(err);

    err = Pa_CloseStream( stream );
    printf( "Pa_CloseStream PortAudio error: %s\n", Pa_GetErrorText(err));

    err = Pa_Terminate();
    if(err != paNoError) PrintAudioError(err);

    // Return
    return ret;
}
