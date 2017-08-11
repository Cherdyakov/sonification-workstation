#ifndef QTMODULATOR_H
#define QTMODULATOR_H

#include "qtoscillator.h"
#include "modulator.h"

class QtModulator : public QtSynthItem
{
    Q_OBJECT

public:
    explicit QtModulator(Modulator* modulator = 0, QObject *parent = 0);
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

    Q_INVOKABLE void setModType(QT_PARAMETER parameter);
    Q_INVOKABLE void setDepth(double depth);
    Q_INVOKABLE void setDepthFixed(bool fixed);
    Q_INVOKABLE void setDepthIndexes(QVector<int> indexes);
    Q_INVOKABLE void setDepthScaled(bool scaled);
    Q_INVOKABLE void setDepthScaleLow(double low);
    Q_INVOKABLE void setDepthScaleHigh(double high);
    Q_INVOKABLE void setDepthScaleExponent(double exponent);

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
    // depth getters
    Q_INVOKABLE double getDepth();
    Q_INVOKABLE bool getDepthFixed();
    Q_INVOKABLE QVector<int> getDepthIndexes();
    Q_INVOKABLE bool getDepthScaled();
    Q_INVOKABLE double getDepthScaleLow();
    Q_INVOKABLE double getDepthScaleHigh();
    Q_INVOKABLE double getDepthScaleExponent();

private:
    Modulator* modulator_;

};

#endif // QTMODULATOR_H
