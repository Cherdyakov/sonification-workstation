#ifndef TRANSPORTWIDGET_H
#define TRANSPORTWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QDial>
#include <QSpinBox>
#include <QLabel>
#include <QDebug>
#include <QTimer>
#include <QCheckBox>

#include "qttransport.h"

using namespace sow;

class TransportWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TransportWidget(QWidget *parent = 0);
    void setTransport(QtTransport* qtTransport);

private:

    bool paused;
    bool looping;
    bool interpolate;
    double stepsPerSecond;
    QPushButton* pauseButton;
    QPushButton* loopButton;
    QCheckBox* interpolateBox;
    QDial* speedDial;
    QSpinBox* speedBox;


signals:
    void pausedChanged(bool pause);
    void loopingChanged(bool loop);
    void speedChanged(int speed);
    void interpolateChanged(bool interpolate);

public slots:
    void on_speed_changed(int speed);
    void on_interpolation_changed(bool interpolation);

private slots:
    void on_pauseButton_released();
    void on_loopButton_released();
    void on_speedBox_valueChanged(int speed);
    void on_interpolateBox_stateChanged(int state);
    void on_datasetChanged(sow::Dataset *dataset);
};

#endif // TRANSPORTWIDGET_H
