#include <QApplication>
#include <QDebug>
#include <QThread>
#include <QQmlContext>

#include "qtsynthitem.h"
#include "qtoscillator.h"
#include "mainwindow.h"
#include "rtaudio/RtAudio.h"
#include "callback.h"
#include "qttransport.h"
#include "ringbuffer.h"
#include "filereader.h"

#define FRAME_RATE 44100
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
    gam::Sync::master().spu(FRAME_RATE);

    RtAudio dac;
//    dac.showWarnings(true);

    //    // Determine the number of devices available
    //    unsigned int devices = dac.getDeviceCount();
    //    // Scan through devices for various capabilities
    //    RtAudio::DeviceInfo info;
    //    for ( unsigned int i=0; i<devices; i++ ) {
    //      info = dac.getDeviceInfo( i );
    //      if ( info.probed == true ) {
    //        // Print, for example, the maximum number of output channels for each device
    //        std::cout << "device = " << i;
    //        std::cout << ": maximum output channels = " << info.outputChannels << "\n";
    //      }
    //    }


    if ( dac.getDeviceCount() < 1 ) {
        qDebug() << "\nNo audio devices found!\n";
        exit( 0 );
    }
    RtAudio::StreamParameters inParams, outParams;
    //temp assignment for my system, eventually need to allow user selection of audio device
    inParams.deviceId = dac.getDefaultInputDevice();
    inParams.nChannels = 2;
    inParams.firstChannel = 0;
    outParams.deviceId = dac.getDefaultOutputDevice();
    outParams.nChannels = 2;
    outParams.firstChannel = 0;

    unsigned int frameRate = FRAME_RATE;
    unsigned int bufferFrames = BLOCK_SIZE;

    try {
        dac.openStream( &outParams, &inParams, RTAUDIO_FLOAT64,
                        frameRate, &bufferFrames, &son::callback, (void *)&uData );
        dac.startStream();
    }
    catch ( RtAudioError& e ) {
        qDebug() << "error";
        e.printMessage();
        //      exit( 0 );
    }

    return a.exec();
}
