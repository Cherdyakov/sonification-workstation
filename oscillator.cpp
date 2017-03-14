#include "oscillator.h"

namespace son {

Oscillator::Oscillator()
{
    waveform = WAVEFORM::SINE;
    gam::Sine<>* defaultGen = new gam::Sine<>(440);
    gens.push_back(defaultGen);
    freqValues.push_back(440.0);
    freqsFixed = true;
}

void Oscillator::parseCommand(SynthItemCommand command)
{
    SYNTH_ITEM_COMMAND_TYPE type = command.type;

    switch (type) {

    case SYNTH_ITEM_COMMAND_TYPE::PARAM_FIXED:
    {
        processSetParameterFixed(command.paramFixed, command.paramName);
        break;
    }
    case SYNTH_ITEM_COMMAND_TYPE::PARAM_INDEXES:
    {
        processSetParameterIndexes(command.paramIndexes, command.paramName);
        break;
    }
    case SYNTH_ITEM_COMMAND_TYPE::PARAM_VALUES:
    {
        processSetParameterValues(command.paramValues, command.paramName);
        break;
    }
    default:
        SynthItem::parseCommand(command);
        break;
    }
}

void Oscillator::processSetWaveform(WAVEFORM waveType)
{
    if (waveform != waveType) {
        waveform = waveType;
    }
}

void Oscillator::processSetFreq(double inFreq)
{
    if (freq != inFreq) {
        freq = inFreq;
    }
}

void Oscillator::processSetFixedFreqs(bool fixed)
{
    freqFixed = fixed;
}

void Oscillator::processSetIndexes(std::vector<int> indexes)
{
    bool m = muted;
    if(!muted) {
        muted = true;
    }
    dataIndexes = indexes;

    resize(dataIndexes.size());

    muted = m;
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
    if(param = FREQS)
    {
        freqIndexes = indexes;
    }
}

void Oscillator::processSetParameterValues(std::vector<double> values, std::__cxx11::string param)
{
    if(param = FREQS)
    {
        freqValues = values;
    }
}

void Oscillator::processSetParameterFixed(bool fixed, std::__cxx11::string param)
{
    if(param = FREQS)
    {
        freqFixed = fixed;
    }
}

float Oscillator::visitChildren()
{
    float s = 0.0;
    for (unsigned int i = 0; i < children.size(); ++i)
    {
        SynthItem* gen = children[i];
        s += gen->process();
    }
    return s;
}

void Oscillator::setFreqs()
{
    if (dataIndexes.size() < 1) //no data mappings, use fixed freq
    {
        for (unsigned int i = 0; i < gens.size(); ++i) {
            gens[i]->freq(freq);
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

