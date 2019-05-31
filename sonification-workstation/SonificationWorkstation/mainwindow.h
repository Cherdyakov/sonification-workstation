#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
    QQuickView* quickView_;
    ThemeManager* themeManager_;

    QString datafile_;
    QString sessionfile_;

    //convenience functions to create and populate menus
    void createActions();
    void createMenus();
    void writeSessionFile();
    void setTheme(const QString theme);
signals:

    void saveSession();

private slots:

    void onQuit();
    void onSave();
    void onSaveAs();
    void onOpen();
    void onImportDataset();
    void onDefaultThemeSet();
    void onContrastThemeSet();
    void onSimpleThemeSet();

};

#endif // MAINWINDOW_H
