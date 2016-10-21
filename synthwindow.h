#ifndef SYNTHWINDOW_H
#define SYNTHWINDOW_H

#include <QMainWindow>
#include <QQuickView>
#include <QMenuBar>

#include "filereader.h"

namespace Ui {
class SynthWindow;
}

class SynthWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SynthWindow(QWidget *parent = 0);
    ~SynthWindow();

    QQuickView *getView() const;
    void setView(QQuickView *value);

private:
    Ui::SynthWindow *ui;
    QQuickView* view;

};

#endif // SYNTHWINDOW_H
