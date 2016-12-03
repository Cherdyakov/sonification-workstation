#ifndef SYNTHWINDOW_H
#define SYNTHWINDOW_H

#include <QMainWindow>
#include <QQuickView>
#include <QMenuBar>

#include "csvreader.h"

class SynthWindow : public QMainWindow
{


public:
    explicit SynthWindow(QWidget *parent = 0);
    ~SynthWindow();

    QQuickView *getView() const;
    void setView(QQuickView *value);
    bool event(QEvent *event);

private:
    QQuickView* view;

};

#endif // SYNTHWINDOW_H
