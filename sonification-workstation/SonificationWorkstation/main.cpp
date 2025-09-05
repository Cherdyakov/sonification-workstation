#include <QApplication>
#include <QQmlContext>
#include "mainwindow.h"
#include "callback.h"
#include "transport.h"
#include "thememanager.h"
#include "Gamma/Sync.h"
#include "Gamma/AudioIO.h"
#include "constants.h"

using namespace sow;

int main(int argc, char *argv[])
{
    // Import Qt Widgets accessiblity plugin.
//    Q_IMPORT_PLUGIN(qtaccessiblewidgets)

    QCoreApplication::setOrganizationName("Sonification Workstation");
    QCoreApplication::setOrganizationDomain("sonificationworkstation.org");
    QCoreApplication::setApplicationName("Sonification Workstation");

    QApplication a(argc, argv);
    qmlRegisterType<ThemeManager>("SoW", 1, 0, "QtThemeManager");
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
    512,            // block size
    constants::SR,  // sample rate (Hz)
    callback,       // user-defined callback
    &uData,         // user data
    2,              // output channels to open
    0               // input channels to open
    );
    audioIO.start();

    // Launch the GUI
    main_window.show();
    main_window.setGeometry(a.primaryScreen()->availableGeometry());

    // Place cleanup code after a.exec, before returning exit code
    const int ret = a.exec();

    // Return
    return ret;
}
