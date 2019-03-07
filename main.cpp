#include <QApplication>
#include <QDebug>
#include <QThread>
#include <QQmlContext>

#include "qtsynthitem.h"
#include "qtoscillator.h"
#include "mainwindow.h"
#include "portaudio.h"
#include "callback.h"
#include "qttransport.h"
#include "ringbuffer.h"
#include "filereader.h"

#define SR 44100
#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    qmlRegisterType<QtSynthItem>("SonLib", 1, 0, "QtSynthItem");
    qmlRegisterType<QtTransport>("SonLib", 1, 0, "QtTransport");
    qmlRegisterType<MainWindow>("MainWindow", 1, 0, "MainWindow");

    MainWindow main_window;
    UserData uData;
    uData.root =  main_window.getTransport()->implementation();

    main_window.show();


    //initialize Gamma
    gam::Sync::master().spu(SR);

    PaStream *stream;
    PaError err;

    err = Pa_Initialize();
    if (err != paNoError ) {
        printf( "Pa_Initialize PortAudio error: %s\n", Pa_GetErrorText(err));
    }

    // Open an audio I/O stream
    err = Pa_OpenDefaultStream( &stream,
                                0,
                                2,
                                paFloat32,
                                SR,
                                256,
                                callback,
                                &uData );

    if ( err != paNoError )
        printf( "Pa_OpenDefaultStream PortAudio error: %s\n", Pa_GetErrorText(err));

    err = Pa_StartStream( stream );
    if ( err != paNoError )
        printf( "Pa_StartStream PortAudio error: %s\n", Pa_GetErrorText(err));


    // Sleep for several seconds to listen
//    Pa_Sleep(3000);

//    err = Pa_AbortStream( stream );
//    if ( err != paNoError )
//        printf( "Pa_AbortStream PortAudio error: %s\n", Pa_GetErrorText(err));

//    err = Pa_CloseStream( stream );
//        printf( "Pa_CloseStream PortAudio error: %s\n", Pa_GetErrorText(err));

//    err = Pa_Terminate();
//    if ( err != paNoError )
//        printf( "Pa_Terminate PortAudio error: %s\n", Pa_GetErrorText(err));

    return a.exec();
}
