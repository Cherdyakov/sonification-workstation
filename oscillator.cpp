#include "oscillator.h"

namespace son {

Oscillator::Oscillator()
{
    defaultGen = new gam::Sine<>(440);
    gens.push_back(defaultGen);
}

int Oscillator::addChild(QObject *child, int type)
{
    SynthItem* item = static_cast<SynthItem*>(child);

    switch (type){
    case AMOD: {
        if(!amods.contains(item))
        {
            return 1; //already child
        }
        amods.push_back(item);
        return 0;
    }
    case FMOD: {
        if(!fmods.contains(item))
        {
            return 1; //already child
        }
        fmods.push_back(item);
        return 0;
    }
    default:
        return 2; //incompatible child type
    }

}

int Oscillator::removeChild(QObject *child)
{
    SynthItem* item = static_cast<SynthItem*>(child);

    int idx;

    idx = amods.indexOf(item);
    if(idx > -1)
    {
        amods.remove(idx);
        return 0;
    }
    idx = fmods.indexOf(item);
    if(idx > -1)
    {
        fmods.remove(idx);
        return 0;
    }

    return 1; //no such child
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

float Oscillator::visitAmods()
{
    float s = 0.0;
    QVector<SynthItem*>::const_iterator i;

    for (i = amods.constBegin(); i != amods.constEnd(); ++i)
    {
        SynthItem* gen = *i;
        s += gen->process();
    }
    return s;
}

float Oscillator::visitFmods()
{
    float s = 0.0;
    QVector<SynthItem*>::const_iterator i;

    for (i = fmods.constBegin(); i != fmods.constEnd(); ++i)
    {
        SynthItem* gen = *i;
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
