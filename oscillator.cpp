#include "oscillator.h"

namespace son {

Oscillator::Oscillator()
{
    waveform = SINE;
    gam::Sine<>* defaultGen = new gam::Sine<>(440);
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

void Oscillator::setDataItem(std::vector<double> *newData)
{
    dataItem = newData;

    for(int i = 0; i < amods.count(); i++) {
        son::SynthItem* item = amods[i];
        item->setDataItem(newData);
    }
    for(int i = 0; i < fmods.count(); i++) {
        son::SynthItem* item = fmods[i];
        item->setDataItem(newData);
    }
}

void Oscillator::setWaveform(SynthItem::WAVEFORM type)
{
    if (waveform != type) {
        waveform = type;
        qDebug() << "cpp: waveform is " << waveform;
    }
}

void Oscillator::setFreq(double inFreq)
{
    if (freq != inFreq) {
        freq = inFreq;
    }
    qDebug() << "cpp: freq is " << freq;
}

bool Oscillator::setIndexes(QVector<int> idxs)
{
    bool m = muted;
    if(!muted) {
        muted = true;
    }
    dataIndexes = idxs;

    resize(dataIndexes.count());

    muted = m;
}

void Oscillator::resize(int size)
{
    bool m = muted;
    if(!muted) {
        muted = true;
    }

    while(gens.count() < size)
    {
        gens.push_back(newGen(waveform));
    }
    while(gens.count() > size)
    {
        gens.removeLast();
    }

    muted = m;

}

gam::AccumPhase<> *Oscillator::newGen(SynthItem::WAVEFORM type)
{
    switch (type) {
    case SINE:
        return new gam::Sine<>(440);
        break;
    case SAW:
        return new gam::Saw<>(440);
        break;
    case SQUARE:
        return new gam::Square<>(440);
    default:
        break;
    }
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
    for (int i = 0; i < gens.count(); ++i) {

        switch (waveform) {
        case SINE:
        {
            gam::Sine<>* gen = static_cast<gam::Sine<>*>(gens[i]);
            sample += gen->operator ()();
            break;
        }
        case SAW:
        {
            gam::Saw<>* gen = static_cast<gam::Saw<>*>(gens[i]);
            sample += gen->operator ()();
            break;
        }
        case SQUARE:
        {
            gam::Square<>* gen = static_cast<gam::Square<>*>(gens[i]);
            sample += gen->operator ()();
            break;
        }
        default:
            break;
        }
    }

    //test noise
    //    sample = ((qrand() * 1.0 / RAND_MAX) - 1.0) * 0.2;
    //test mssg
    //qDebug() << "processOscillator";

    //test noise
    //    sample = ((qrand() * 1.0 / RAND_MAX) - 1.0) * 0.2;

    return sample / gens.count();
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
    if (dataIndexes.count() < 1) //no data mappings, use fixed freq
    {
        for (int i = 0; i < gens.count(); ++i) {
            gens[i]->freq(freq);
        }
    }
    else //map each indexed value from the data row to the freq of a generator
    {
        for (int i = 0; (i < gens.count()) &&
             (i < dataIndexes.count()) &&
             (i < dataItem->size()); ++i) {
            double f = dataItem->at(dataIndexes[i]);
            gens[i]->freq(f);
        }
    }
}

}
