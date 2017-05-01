#ifndef QTTRANSPORT_H
#define QTTRANSPORT_H

#include <QObject>

#include "transport.h"
#include "qtoscillator.h"
#include "qtaudifier.h"
#include "qtmodulator.h"
#include <QTimer>

using namespace son;

class QtTransport : public QtSynthItem
{
    Q_OBJECT
    Q_ENUMS(ITEM)
public:

    enum ITEM {
        OUT = (int)SynthItem::ITEM::TRANSPORT,
        OSCILLATOR,
        AUDIFIER,
        MODULATOR
    };

    explicit QtTransport(SynthItem* item = 0, QObject *parent = 0);

    Q_INVOKABLE QtSynthItem* createItem(ITEM type);
    float process();

public slots:
    // slots for controlling playback
    void on_pausedChanged(bool on_pausedChanged);
    void on_posChanged(double pos);
    void on_speedChanged(double speed);
    void on_loopingChanged(bool looping);
    void on_loopPointsChanged(double begin, double end);
    void on_dataChanged(std::vector<double>* data, unsigned int height, unsigned int width);
    void on_interpolateChanged(bool interpolate);

    // for polling state from outside
    // (i.e. GUI)
    double getPos();

private:

signals:
    void posChanged(double pos);

private slots:
    void updatePos();

};

#endif // QTTRANSPORT_H
