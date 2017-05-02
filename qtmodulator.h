#ifndef QTMODULATOR_H
#define QTMODULATOR_H

#include "qtoscillator.h"
#include "modulator.h"

class QtModulator : public QtOscillator
{
    Q_OBJECT

public:
    explicit QtModulator(Modulator* modulator = 0, QObject *parent = 0);
    virtual SynthItem* implementation() override;

    Q_INVOKABLE virtual void deleteItem() override;
    Q_INVOKABLE virtual void addParent(QtSynthItem* parent) override;
    Q_INVOKABLE virtual void removeParent(QtSynthItem* parent) override;
    Q_INVOKABLE virtual bool addChild(QtSynthItem *child, PARAMETER param) override;
    Q_INVOKABLE virtual void removeChild(QtSynthItem *child) override;
    Q_INVOKABLE virtual void mute(bool mute) override;

    Q_INVOKABLE void setFreq(double freq);
    Q_INVOKABLE void setFreqFixed(bool fixed);
    Q_INVOKABLE void setFreqIndexes(QVector<int> indexes);
    Q_INVOKABLE void setFreqScaled(bool scaled);
    Q_INVOKABLE void setFreqScaleVals(double low, double high, double exp);

    Q_INVOKABLE void setModType(PARAMETER parameter);
    Q_INVOKABLE void setDepth(double depth);
    Q_INVOKABLE void setDepthFixed(bool fixed);
    Q_INVOKABLE void setDepthIndexes(QVector<int> indexes);
    Q_INVOKABLE void setDepthScaled(bool scaled);
    Q_INVOKABLE void setDepthScaleVals(double low, double high, double exp);

private:
    Modulator* modulator_;

};

#endif // QTMODULATOR_H
