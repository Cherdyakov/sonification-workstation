#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include <QObject>
#include "synthitem.h"
#include "Gamma/Oscillator.h"

namespace son {
class Oscillator;
}

class son::Oscillator : public SynthItem
{
    Q_OBJECT

public:
    Oscillator();
    float process();
    using SynthItem::addChild;
    void addChild(QObject* child, int type);
    void removeChild(QObject* child);
    void setDataColumn(QVector<double>* col);

    //UI invokable functions for setting parameters
    Q_INVOKABLE void setWaveform(WAVEFORM type);
    Q_INVOKABLE void setFreq(double inFreq);
    Q_INVOKABLE bool setIndexes(QVector<int> idxs);

private:

    QVector<int> dataIndexes;

    double freq;

    //for scaling the input
//    double dataMin;
//    double dataMax;
//    float freqMin;
//    float freqMax;

    WAVEFORM waveform;

    QVector<gam::AccumPhase<>*> gens;

    QVector<SynthItem*> amods;
    QVector<SynthItem*> fmods;

    void resize(int size);
    gam::AccumPhase<>* newGen(WAVEFORM type);

    float visitFmods();
    float visitAmods();
    void setFreqs();

};

#endif // OSCILLATOR_H
