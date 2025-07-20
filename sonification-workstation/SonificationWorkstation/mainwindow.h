#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGuiApplication>
#include <QQmlContext>
#include <QQuickView>
#include <QAction>
#include <QLayout>
#include <QSettings>

#include "trackview.h"
#include "transport.h"
#include "transportwidget.h"
#include "filereader.h"
#include "thememanager.h"
#include "aboutmessage.h"
#include "datasetimportdialog.h"

using namespace sow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Transport* getTransport();

private:

    Transport* transport_;
    TransportWidget* transportWidget_;
    PlayHead* playhead_;
    QQuickView* quickView_;
    ThemeManager* themeManager_;
    Dataset* dataset_;
    DataProcessorController* dataProcessorController_;

    QString datafile_;
    QString sessionfile_;
    bool horizontalData_;
    AboutMessage about_;

    // Convenience functions to create and populate menus.
    void createActions();
    void createMenus();
    void writeSessionFile();
    void setTheme(const QString theme);

signals:

    void saveSession();
    void datasetChanged(Dataset* dataset);

public slots:

    void onRecordChanged(bool record);
    void onImportDatasetReady();

private slots:

    void onQuit();
    void onSave();
    void onSaveAs();
    void onOpen();
    void onImportDataset();
    void onDefaultThemeSet();
    void onContrastThemeSet();
    void onSimpleThemeSet();
    void onAbout();

};

#endif // MAINWINDOW_H
