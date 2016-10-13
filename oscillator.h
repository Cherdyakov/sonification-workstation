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
    void addChild(QObject* child, int type);
    void removeChild(QObject* child);
    Q_INVOKABLE void setWaveform(WAVEFORM type);

private:

    QVector<double> data;

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
    void setAmps();

};

} //namespace son

#endif // OSCILLATOR_H
