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
    Q_INVOKABLE void setFreqScaleLow(double low);
    Q_INVOKABLE void setFreqScaleHigh(double high);
    Q_INVOKABLE void setFreqScaleExponent(double exponent);

    // getters
    Q_INVOKABLE bool getMute();
    // frequency getters
    Q_INVOKABLE double getFreq();
    Q_INVOKABLE bool getFreqFixed();
    Q_INVOKABLE QVector<int> getFreqIndexes();
    Q_INVOKABLE bool getFreqScaled();
    Q_INVOKABLE double getFreqScaleLow();
    Q_INVOKABLE double getFreqScaleHigh();
    Q_INVOKABLE double getFreqScaleExponent();

private:
    Oscillator* oscillator_;
};

#endif // QTOSCILLATOR_H
