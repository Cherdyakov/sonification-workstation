#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include <QObject>
#include "synthitem.h"
#include "Gamma/Oscillator.h"

namespace son {

class Oscillator : public SynthItem
{
    Q_OBJECT
public:
    Oscillator();
    float process();
    using SynthItem::addChild;
    void addChild(QObject* child, int type);
    void removeChild(QObject* child);
    void setDataColumn(QVector<double>* data);

    //UI invokable functions for setting parameters
    Q_INVOKABLE void setWaveform(WAVEFORM type);
    Q_INVOKABLE void setFixedFreq(bool fixed);
    Q_INVOKABLE void setFreq(double inFreq);

private:

    QVector<double>* dataColumn;


    bool fixedFreq;
    double freq;

    //for scaling the input
//    double dataMin;
//    double dataMax;
//    float freqMin;
//    float freqMax;

    WAVEFORM waveform;
    gam::Sine<>* defaultGen;

    QVector<gam::Sine<>*> gens;
    QVector<SynthItem*> amods;
    QVector<SynthItem*> fmods;

    float visitFmods();
    float visitAmods();
    void setFreqs();

};

} //namespace son

#endif // OSCILLATOR_H
