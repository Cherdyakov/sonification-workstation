#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QDial>
#include <QSpinBox>
#include <QLabel>
#include <QDebug>
#include <QTimer>

#include "synthgraph.h"

class Transport : public QWidget
{
    Q_OBJECT
public:
    explicit Transport(QWidget *parent = 0);
    void setSynthGraph(son::SynthGraph* graph);

private:

    bool paused;
    double stepsPerSecond;
    QPushButton* pauseButton;
    QDial* speedDial;
    QDoubleSpinBox* speedBox;
    son::SynthGraph* synthGraph;


signals:
    void cursorPosChanged(double pos);
    void pausedChanged(bool pause);

public slots:
    void on_datasetChanged(std::vector<double> *data, uint height, uint width);

private slots:
    void updateCursorPos();
    void on_pauseButton_released();
    void on_speedBox_valueChanged(double s);
};

#endif // TRANSPORT_H
