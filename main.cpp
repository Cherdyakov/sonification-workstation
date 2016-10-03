#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QThread>
#include <QQmlContext>

#include "rtaudio/RtAudio.h"
#include "callback.h"
#include "synthgraph.h"
#include "oscillator.h"

int main(int argc, char *argv[])
{

    son::UserData uData;
    son::SynthGraph* graph = new son::SynthGraph();
    uData.graph = graph;

    qmlRegisterType<son::SynthGraph>("son.lib", 1, 0, "SynthGraph");
    qmlRegisterType<son::SynthItem>("son.lib", 1, 0, "SynthItemImplementation");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("graph", graph);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));




    //connect signals and slots
//    QObject::connect(&engine, SIGNAL(quit()), qApp, SLOT(quit()));

    //initialize Gamma
    gam::Sync::master().spu(44100);

    RtAudio dac;
    dac.showWarnings(true);

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

    unsigned int sampleRate = 44100;
    unsigned int bufferFrames = 512; // 256 sample frames


    try {
      dac.openStream( &outParams, &inParams, RTAUDIO_FLOAT64,
                      sampleRate, &bufferFrames, &son::callback, (void *)&uData );
      dac.startStream();
    }
    catch ( RtAudioError& e ) {
      qDebug() << "error";
      e.printMessage();
//      exit( 0 );
    }

//    char input;
//    std::cout << "\nPlaying ... press <enter> to quit.\n";
//    std::cin.get( input );
//    try {
//      // Stop the stream
//      dac.stopStream();
//    }
//    catch (RtAudioError& e) {
//      e.printMessage();
//    }
//    if ( dac.isStreamOpen() ) dac.closeStream();


    return app.exec();
}
