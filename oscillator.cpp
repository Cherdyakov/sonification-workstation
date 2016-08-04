#include "oscillator.h"

namespace son {

Oscillator::Oscillator()
{
    defaultGen = new gam::Sine<>(440);
    gens.push_back(defaultGen);
}

float Oscillator::process()
{
    //sample we will ultimately return
    float sample = 0.0;
    //sample set by any connected amplitude modulators
    float amSample = 1.0;
    //sample set by any connected frequency modulators
    float fmSample = 1.0;

    //check fmods
    if(!fmods.isEmpty())
        fmSample = visitFmods();

    //check amods
    if(!amods.isEmpty())
        amSample = visitAmods();

    //set freqs

    //set amps

    //generate sample
    QVector<gam::Sine<>*>::const_iterator i;

    for (i = gens.constBegin(); i != gens.constEnd(); ++i) {
        gam::Sine<>* sine = *i;
        sample += sine->operator ()();
    }

    //return sample

    //test noise
    //    sample = ((qrand() * 1.0 / RAND_MAX) - 1.0) * 0.2;
    //test mssg
    //qDebug() << "processOscillator";

    return sample;
}

float Oscillator::visitFmods()
{
    float s = 0.0;
    QVector<son::Oscillator*>::const_iterator i;

    for (i = fmods.constBegin(); i != fmods.constEnd(); ++i)
    {
        son::Oscillator* gen = *i;
        s += gen->process();
    }
    return s;
}

float Oscillator::visitAmods()
{
    float s = 0.0;
    QVector<son::Oscillator*>::const_iterator i;

    for (i = fmods.constBegin(); i != fmods.constEnd(); ++i)
    {
        son::Oscillator* gen = *i;
        s += gen->process();
    }
    return s;
}

void Oscillator::setFreqs()
{
    float f = 440;
    QVector<gam::Sine<>*>::const_iterator i;

    for (i = gens.constBegin(); i != gens.constEnd(); ++i) {
        gam::Sine<>* sine = *i;
        sine->freq(f);
    }
}

void Oscillator::setAmps()
{

}



}
