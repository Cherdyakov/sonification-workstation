#ifndef QTTRANSPORT_H
#define QTTRANSPORT_H

#include <QObject>
#include <QTimer>

#include "transport.h"
#include "qtoscillator.h"
#include "qtaudifier.h"
#include "qtmodulator.h"
#include "qtpanner.h"
#include "qtenvelope.h"
#include "qtvolume.h"
#include "qtnoise.h"
#include "qtequalizer.h"

using namespace son;

class QtTransport : public QtSynthItem
{
    Q_OBJECT
    Q_ENUMS(QT_ITEM)
public:

    enum QT_ITEM {
        OUT = (int)SynthItem::ITEM::TRANSPORT,
        OSCILLATOR,
        AUDIFIER,
        MODULATOR,
        PANNER,
        ENVELOPE,
        VOLUME,
        NOISE,
        EQUALIZER
    };

    explicit QtTransport(QObject *parent = 0);
    virtual SynthItem* implementation() override;

    Q_INVOKABLE QtSynthItem* createItem(QT_ITEM type);
    Q_INVOKABLE virtual void deleteSelf() override;
    Q_INVOKABLE virtual void addParent(QtSynthItem* parent) override;
    Q_INVOKABLE virtual void removeParent(QtSynthItem* parent) override;
    Q_INVOKABLE virtual bool addChild(QtSynthItem *child, QT_PARAMETER param) override;
    Q_INVOKABLE virtual void removeChild(QtSynthItem *child) override;
    Q_INVOKABLE virtual void mute(bool mute) override;
    Q_INVOKABLE void deleteItem(QtSynthItem* item);
    Q_INVOKABLE void subscribeItem(QtSynthItem* item);

public slots:

    // slots for controlling playback
    void on_dataChanged(std::vector<double>* data, unsigned int height, unsigned int width);
    void on_pausedChanged(bool on_pausedChanged);
    void on_posChanged(double pos);
    void on_speedChanged(int speed);
    void on_loopingChanged(bool looping);
    void on_loopPointsChanged(double begin, double end);
    void on_interpolateChanged(bool interpolate);

    // for polling state from outside
    // (i.e. GUI)
    double getPos();

private:
    Transport transport_;

signals:
    void posChanged(double pos);

private slots:
    void updatePos();

};

#endif // QTTRANSPORT_H
