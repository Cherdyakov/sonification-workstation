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

    Q_INVOKABLE void setFixedFreq(double freq);
    Q_INVOKABLE void setUseFixedFreq(bool fixed);
    Q_INVOKABLE void setUseFreqScaling(bool scaling);
    Q_INVOKABLE void setFreqScalingVals(double low, double high, double exp);

    private:
};

#endif // QTOSCILLATOR_H
