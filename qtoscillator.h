#ifndef QTOSCILLATOR_H
#define QTOSCILLATOR_H

#include <QObject>
#include "oscillator.h"

using namespace son;

class QtOscillator : public QObject
{
    Q_OBJECT
public:
    explicit QtOscillator(QObject *parent = 0);
    void addChild(SynthItem* child, SynthItem::SON_CHILD_TYPE type);
    void removeChild(SynthItem* child);
    void setDataItem(std::vector<double> *data);

    Q_INVOKABLE void setWaveform(SynthItem::SON_WAVEFORM waveform);
    Q_INVOKABLE void setFreq(double freq);
    Q_INVOKABLE void setFixedFreqs(bool fixed);
    Q_INVOKABLE void setIndexes(std::vector<int> indexes);

private:
    Oscillator oscillator;
signals:

public slots:
};

#endif // QTOSCILLATOR_H
