#include "oscillator.h"

namespace son {

Oscillator::Oscillator()
{
    defaultGen = new gam::Sine<>(440);
    gens.push_back(defaultGen);
    freq = 440;
}

void Oscillator::addChild(QObject *child, int type)
{
    SynthItem* item = static_cast<SynthItem*>(child);

    switch (type){
    case AMOD: {
        if(!amods.contains(item))
        {
            return; //already child
        }
        amods.push_back(item);
        break;
    }
    case FMOD: {
        if(!fmods.contains(item))
        {
            return; //already child
        }
        fmods.push_back(item);
        break;
    }
    default:
        break; //incompatible child type
    }

}

void Oscillator::removeChild(QObject *child)
{
    SynthItem* item = static_cast<SynthItem*>(child);

    int idx;

    idx = amods.indexOf(item);
    if(idx > -1)
    {
        amods.remove(idx);
        return;
    }

    idx = fmods.indexOf(item);
    if(idx > -1)
    {
        fmods.remove(idx);
    } //no such child
}

void Oscillator::setDataColumn(QVector<double> *data)
{
    dataColumn = data;
}

void Oscillator::setWaveform(SynthItem::WAVEFORM type)
{
    if (waveform != type) {
        waveform = type;
        qDebug() << "cpp: waveform is " << waveform;
    }
}

void Oscillator::setFixedFreq(bool fixed)
{
    if (fixedFreq != fixed) {
        fixedFreq = fixed;
    }
    qDebug() << "cpp: fixedFreq is " << fixedFreq;
}

void Oscillator::setFreq(double inFreq)
{
    if (freq != inFreq) {
        freq = inFreq;
    }
    qDebug() << "cpp: freq is " << freq;
}

float Oscillator::process()
{
    //sample we will ultimately return
    float sample = 0.0;

    if(muted)
    {
        return sample;
    }
//    //sample set by any connected amplitude modulators
//    float amSample = 1.0;
//    //sample set by any connected frequency modulators
//    float fmSample = 1.0;

//    //check fmods
//    if(!fmods.isEmpty())
//        fmSample = visitFmods();

//    //check amods
//    if(!amods.isEmpty())
//        amSample = visitAmods();

    //set frequencies
    setFreqs();


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

    //test noise
//    sample = ((qrand() * 1.0 / RAND_MAX) - 1.0) * 0.2;



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
    float f = freq;
    QVector<gam::Sine<>*>::const_iterator i;

    for (i = gens.constBegin(); i != gens.constEnd(); ++i) {
        gam::Sine<>* sine = *i;
        sine->freq(f);
    }
}

}
