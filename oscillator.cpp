#include "oscillator.h"

namespace son {

Oscillator::Oscillator()
{
    waveform = WAVEFORM::SINE;
    gam::Sine<>* defaultGen = new gam::Sine<>(440);
    gens.push_back(defaultGen);
    freqValues.push_back(440.0);
    freqFixed = true;
}

void Oscillator::resize(unsigned int size)
{
    bool m = muted;
    if(!muted) {
        muted = true;
    }

    while(gens.size() < size)
    {
        gens.push_back(newGen(waveform));
    }
    while(gens.size() > size)
    {
        gens.pop_back();
    }

    muted = m;

}

gam::AccumPhase<> *Oscillator::newGen(WAVEFORM type)
{
    switch (type) {
    case WAVEFORM::SINE:
        return new gam::Sine<>(440);
        break;
    case WAVEFORM::SAW:
        return new gam::Saw<>(440);
        break;
    case WAVEFORM::SQUARE:
        return new gam::Square<>(440);
    default:
        return NULL;
        break;
    }
}

float Oscillator::process()
{
    float sample = 0.0;

    if(!commandBuffer.empty())
    {
        retrieveCommands();
    }

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
    for (unsigned int i = 0; i < gens.size(); ++i) {

        switch (waveform) {
        case WAVEFORM::SINE:
        {
            gam::Sine<>* gen = static_cast<gam::Sine<>*>(gens[i]);
            sample += gen->operator ()();
            break;
        }
        case WAVEFORM::SAW:
        {
            gam::Saw<>* gen = static_cast<gam::Saw<>*>(gens[i]);
            sample += gen->operator ()();
            break;
        }
        case WAVEFORM::SQUARE:
        {
            gam::Square<>* gen = static_cast<gam::Square<>*>(gens[i]);
            sample += gen->operator ()();
            break;
        }
        default:
            break;
        }
    }
    return sample / gens.size();
}

void Oscillator::processSetParameterIndexes(std::vector<int> indexes, std::__cxx11::string param)
{
    if(param == kFrequency)
    {
        freqIndexes = indexes;
    }
}

void Oscillator::processSetParameterValues(std::vector<double> values, std::__cxx11::string param)
{
    if(param == kFrequency)
    {
        freqValues = values;
    }
    if(param == kWaveform)
    {
        if(wave)
    }
}

void Oscillator::processSetParameterFixed(bool fixed, std::__cxx11::string param)
{
    if(param == kFrequency)
    {
        freqFixed = fixed;
    }
}

void Oscillator::visitChildren()
{
    amSample = 0.0;
    fmSample = 0.0;
    for (unsigned int i = 0; i < fmChildren.size(); ++i)
    {
        SynthItem* gen = fmChildren[i];
        fmSample += gen->process();
    }
    for (unsigned int i = 0; i < amChildren.size(); ++i)
    {
        SynthItem* gen = amChildren[i];
        amSample += gen->process();
    }
}

void Oscillator::setFreqs()
{
    if (freqIndexes.size() < 1) //no data mappings, use fixed freq
    {
        for (unsigned int i = 0; i < gens.size(); ++i) {
            gens[i]->(freq);
        }
    }
    else //map each indexed value from the data row to the freq of a generator
    {
        for (unsigned int i = 0; (i < gens.size()) &&
             (i < dataIndexes.size()) &&
             (i < dataItem->size()); ++i) {
            double f = dataItem->at(dataIndexes[i]);
            gens[i]->freq(f);
        }
    }

}

}

// clipboard

