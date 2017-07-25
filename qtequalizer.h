#ifndef QTEQUALIZER_H
#define QTEQUALIZER_H

#include "qtsynthitem.h"
#include "equalizer.h"

using namespace  son;

class QtEqualizer : public QtSynthItem
{
    Q_OBJECT

public:
    explicit QtEqualizer(Equalizer *equalizer = 0, QObject *parent = 0);
    virtual SynthItem* implementation() override;

    Q_INVOKABLE virtual void deleteItem() override;
    Q_INVOKABLE virtual void addParent(QtSynthItem* parent) override;
    Q_INVOKABLE virtual void removeParent(QtSynthItem* parent) override;
    Q_INVOKABLE virtual bool addChild(QtSynthItem *child, QT_PARAMETER param) override;
    Q_INVOKABLE virtual void removeChild(QtSynthItem *child) override;
    Q_INVOKABLE virtual void mute(bool mute) override;

    Q_INVOKABLE void setFrequency(double frequency);
    Q_INVOKABLE void setFrequencyFixed(bool fixed);
    Q_INVOKABLE void setFrequencyIndexes(QVector<int> indexes);
    Q_INVOKABLE void setFrequencyScaled(bool scaled);
    Q_INVOKABLE void setFrequencyScaleVals(double low, double high, double exp);

    Q_INVOKABLE void setResonance(double resonance);
    Q_INVOKABLE void setResonanceFixed(bool fixed);
    Q_INVOKABLE void setResonanceIndexes(QVector<int> indexes);
    Q_INVOKABLE void setResonanceScaled(bool scaled);
    Q_INVOKABLE void setResonanceScaleVals(double low, double high, double exp);

    Q_INVOKABLE void setFilterType(QT_FILTER_TYPES type);

private:
    Equalizer* equalizer_;
};

#endif // QTEQUALIZER_H
