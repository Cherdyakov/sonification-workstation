#ifndef QTTRANSPORT_H
#define QTTRANSPORT_H

#include <QObject>

#include "transport.h"
#include "qtoscillator.h"
#include "qtaudifier.h"
#include "qtmodulator.h"

using namespace son;

class QtTransport : public QObject
{
    Q_OBJECT
    Q_ENUMS(ITEM)
public:

    enum ITEM {
        OUT = (int)SynthItem::ITEM::OUT,
        OSCILLATOR,
        AUDIFIER,
        MODULATOR
    };

    explicit QtTransport(QObject *parent = 0);

    Q_INVOKABLE QtSynthItem* createItem(ITEM type);
    float process();
    int graphSize();

    // functions for controlling playback
    void pause(bool pause);
    void setPos(double pos);
    void setSpeed(double speed);
    void setLooping(bool looping);
    void setLoopPoints(double begin, double end);
    void setData(std::vector<double>* data, unsigned int height, unsigned int width);
    void setInterpolate(bool interpolate);

    // for polling state from outside
    // (i.e. GUI)
    double getPos();

private:
    Transport transport;

signals:

public slots:
};

#endif // QTTRANSPORT_H
