#ifndef QTMODULATOR_H
#define QTMODULATOR_H

#include "qtoscillator.h"
#include "modulator.h"

class QtModulator : public QtOscillator
{
    Q_OBJECT

public:
    explicit QtModulator(SynthItem* item = 0, QObject *parent = 0);
    Q_INVOKABLE void setModulationParameter(PARAMETER parameter);
    Q_INVOKABLE void setDepth(double depth);
    Q_INVOKABLE void setUseFixedDepth(bool fixed);
    Q_INVOKABLE void setUseDepthScaling(bool scaling);
    Q_INVOKABLE void setDepthScalingVals(double low, double high, double exp);

private:
    Modulator* modulator;

};

#endif // QTMODULATOR_H
