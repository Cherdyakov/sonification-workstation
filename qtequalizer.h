#ifndef QTEQUALIZER_H
#define QTEQUALIZER_H

#include "qtsynthitem.h"
#include "equalizer.h"

using namespace sow;

class QtEqualizer : public QtSynthItem
{
    Q_OBJECT

public:
    explicit QtEqualizer(Equalizer *equalizer = 0, QObject *parent = 0);
    virtual SynthItem* implementation() override;

    Q_INVOKABLE virtual void deleteSelf() override;
    Q_INVOKABLE virtual void addParent(QtSynthItem* parent) override;
    Q_INVOKABLE virtual void removeParent(QtSynthItem* parent) override;
    Q_INVOKABLE virtual bool addChild(QtSynthItem *child, QT_PARAMETER param) override;
    Q_INVOKABLE virtual void removeChild(QtSynthItem *child) override;
    Q_INVOKABLE virtual void mute(bool mute) override;

    Q_INVOKABLE void setFrequency(double frequency);
    Q_INVOKABLE void setFrequencyFixed(bool fixed);
    Q_INVOKABLE void setFrequencyIndexes(QVector<int> indexes);
    Q_INVOKABLE void setFrequencyScaled(bool scaled);
    Q_INVOKABLE void setFrequencyScaleLow(double low);
    Q_INVOKABLE void setFrequencyScaleHigh(double high);
    Q_INVOKABLE void setFrequencyScaleExponent(double exponent);

    Q_INVOKABLE void setResonance(double resonance);
    Q_INVOKABLE void setResonanceFixed(bool fixed);
    Q_INVOKABLE void setResonanceIndexes(QVector<int> indexes);
    Q_INVOKABLE void setResonanceScaled(bool scaled);
    Q_INVOKABLE void setResonanceScaleLow(double low);
    Q_INVOKABLE void setResonanceScaleHigh(double high);
    Q_INVOKABLE void setResonanceScaleExponent(double exponent);

    Q_INVOKABLE void setFilterType(QT_FILTER_TYPES type);

    // getters
    Q_INVOKABLE bool getMute();
    // frequency getters
    Q_INVOKABLE double getFrequency();
    Q_INVOKABLE bool getFrequencyFixed();
    Q_INVOKABLE QVector<int> getFrequencyIndexes();
    Q_INVOKABLE bool getFrequencyScaled();
    Q_INVOKABLE double getFrequencyScaleLow();
    Q_INVOKABLE double getFrequencyScaleHigh();
    Q_INVOKABLE double getFrequencyScaleExponent();
    // resonance getters
    Q_INVOKABLE double getResonance();
    Q_INVOKABLE bool getResonanceFixed();
    Q_INVOKABLE QVector<int> getResonanceIndexes();
    Q_INVOKABLE bool getResonanceScaled();
    Q_INVOKABLE double getResonanceScaleLow();
    Q_INVOKABLE double getResonanceScaleHigh();
    Q_INVOKABLE double getResonanceScaleExponent();

private:
    Equalizer* equalizer_;
};

#endif // QTEQUALIZER_H
