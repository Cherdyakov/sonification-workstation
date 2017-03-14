#ifndef QTOSCILLATOR_H
#define QTOSCILLATOR_H

#include <QObject>
#include "qtsynthitem.h"
#include "oscillator.h"

using namespace son;

class QtOscillator : public QtSynthItem
{
    Q_OBJECT
public:

    explicit QtOscillator(SynthItem* item = 0, QObject *parent = 0);
    void addChild(QtSynthItem* child, CHILD_TYPE type) override;
    void removeChild(QtSynthItem* child) override;

    Q_INVOKABLE void setWaveform(WAVEFORM waveform);
    Q_INVOKABLE void setFreq(double freq);
    Q_INVOKABLE void setFixedFreqs(bool fixed);

signals:

public slots:
};

#endif // QTOSCILLATOR_H
