#ifndef QTOSCILLATOR_H
#define QTOSCILLATOR_H

#include "qtsynthitem.h"
#include "oscillator.h"

using namespace son;

class QtOscillator : public QtSynthItem
{
    Q_OBJECT
public:

    explicit QtOscillator(Oscillator *oscillator = 0, QObject *parent = 0);
    virtual SynthItem* implementation() override;

    Q_INVOKABLE virtual void deleteItem() override;
    Q_INVOKABLE virtual void addParent(QtSynthItem* parent) override;
    Q_INVOKABLE virtual void removeParent(QtSynthItem* parent) override;
    Q_INVOKABLE virtual bool addChild(QtSynthItem *child, QT_PARAMETER param) override;
    Q_INVOKABLE virtual void removeChild(QtSynthItem *child) override;
    Q_INVOKABLE virtual void mute(bool mute) override;

    Q_INVOKABLE void setFreq(double freq);
    Q_INVOKABLE void setFreqFixed(bool fixed);
    Q_INVOKABLE void setFreqIndexes(QVector<int> indexes);
    Q_INVOKABLE void setFreqScaled(bool scaled);
    Q_INVOKABLE void setFreqScaleVals(double low, double high, double exp);

private:
    Oscillator* oscillator_;
};

#endif // QTOSCILLATOR_H
