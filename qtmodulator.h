#ifndef QTMODULATOR_H
#define QTMODULATOR_H

#include "qtoscillator.h"
#include "modulator.h"

class QtModulator : public QtOscillator
{
    Q_OBJECT

public:
    explicit QtModulator(SynthItem* item = 0, QObject *parent = 0);
    Q_INVOKABLE void setModType(CHILD_TYPE childType);
    Q_INVOKABLE void setDepth(double depth);

private:
    Modulator* modulator;

};

#endif // QTMODULATOR_H
