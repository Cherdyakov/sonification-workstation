#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QDial>
#include <QSpinBox>
#include <QLabel>
#include <QDebug>

#include "synthgraph.h"

namespace son {
class Transport;
}

class son::Transport : public QWidget
{
    Q_OBJECT
public:
    explicit Transport(QWidget *parent = 0);

private:
    int dataHeight;
    int dataWidth;
    int dataDepth;
    bool horizontal;
    bool paused;
    int stepsPerSecond;
    QPushButton* pauseButton;
    QDial* speedDial;
    QSpinBox* speedBox;
    son::SynthGraph* synthGraph;

signals:
    void pauseChanged(bool paused);

public slots:
    void on_dataDimensionsChanged(int h, int w, int d);

private slots:
    void on_pauseButton_released();
    void on_speedBox_valueChanged(int s);
};

#endif // TRANSPORT_H
