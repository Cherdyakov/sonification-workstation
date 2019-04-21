#include <QApplication>
#include <QQmlContext>
#include "mainwindow.h"
#include "portaudio.h"
#include "callback.h"
#include "transport.h"
#include "filereader.h"
#include "Gamma/Sync.h"
#include "Gamma/AudioIO.h"
#include "constants.h"

using namespace sow;

int main(int argc, char *argv[])
{

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QApplication a(argc, argv);
    qmlRegisterType<SynthItem>("SoW", 1, 0, "QtSynthItem");
    qmlRegisterType<Oscillator>("SoW", 1, 0, "QtOscillator");
    qmlRegisterType<Transport>("SoW", 1, 0, "QtTransport");
    qmlRegisterType<ParameterFloatInterface>("SoW", 1, 0, "SowParameter");
    qmlRegisterType<MainWindow>("MainWindow", 1, 0, "MainWindow");
    qmlRegisterType<ENUMS>("ENUMS", 1, 0, "ENUMS");
    qRegisterMetaType<ENUMS::ITEM_TYPE>();    qRegisterMetaType<ENUMS::PARAMETER>();

    MainWindow main_window;
    UserData uData;
    uData.root =  main_window.getTransport();

    // Initialize Gamma
    gam::Sync::master().spu(constants::SR);

    AudioIO audioIO(
    128,        // block size
    44100,      // sample rate (Hz)
    callback,   // user-defined callback
    &uData,     // user data
    2,          // input channels to open
    2           // output
    );
    audioIO.start();

    // Launch the GUI
    main_window.show();

    // Place cleanup code after a.exec, before returning exit code
    const int ret = a.exec();

    // Return
    return ret;
}
