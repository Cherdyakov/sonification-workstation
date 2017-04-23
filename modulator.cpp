#include "modulator.h"

namespace son {

Modulator::Modulator()
{
    myType = ITEM_TYPE::MODULATOR;
    modType = ITEM_CHILD_TYPE::AMOD;
    waveform = WAVEFORM::SINE;
    fixedFreq = 440;
    useFixedFreq = true;
    useFreqScaling = true;
    freqScaleLow = 40;
    freqScaleHigh = 16000;
    acceptedChildTypes = {
        ITEM_CHILD_TYPE::AMOD,
        ITEM_CHILD_TYPE::FMOD
    };

    gen = new gam::Sine<>(fixedFreq);
}

float Modulator::process()
{
    float sample = 0;

    if(!commandBuffer.empty())
    {
        retrieveCommands();
    }

    if(muted)
    {
        return sample;
    }

    //set frequency of generator
    setFreqs();

    //generate sample

    switch (waveform) {
    case WAVEFORM::SINE:
    {
        gam::Sine<>* g = static_cast<gam::Sine<>*>(gen);
        sample += g->operator ()();
        break;
    }
    case WAVEFORM::SAW:
    {
        gam::Saw<>* g = static_cast<gam::Saw<>*>(gen);
        sample += g->operator ()();
        break;
    }
    case WAVEFORM::SQUARE:
    {
        gam::Square<>* g = static_cast<gam::Square<>*>(gen);
        sample += g->operator ()();
        break;
    }
    default:
        break;
    }

    //check amods
    if(!amods.empty())
    {
        float amSample = visitAmods();
        sample *= amSample;
    }

    return sample;
}

void Modulator::setModType(SynthItem::ITEM_CHILD_TYPE childType)
{
    SynthItemCommand command;
    command.type = ITEM_COMMAND_TYPE::VALUE;
    command.parameter = ITEM_PARAMETER::MODULATION;
    command.childType = childType;
    commandBuffer.push(command);
}

void Modulator::processCommand(SynthItem::SynthItemCommand command)
{
    ITEM_COMMAND_TYPE type = command.type;

    switch (type) {
    case ITEM_COMMAND_TYPE::VALUE:
    {
        if(command.parameter == ITEM_PARAMETER::MODULATION)
        {
            processSetModType(command.childType);
        }
        break;
    }
    default:
        Oscillator::processCommand(command);
        break;
    }
}

void Modulator::processSetWaveform(WAVEFORM waveform)
{
    if(this->waveform == waveform) {
        return;
    }
    bool wasMuted = muted;
    if(!muted) {
        muted = true;
    }
    this->waveform = waveform;
    delete gen;
    switch (this->waveform) {
    case WAVEFORM::SINE:
        gen = new gam::Sine<>(440);
        break;
    case WAVEFORM::SAW:
        gen = new gam::Saw<>(440);
        break;
    case WAVEFORM::SQUARE:
        gen = new gam::Square<>(440);
    default:
        break;
    }
    muted = wasMuted;
}

void Modulator::setFreqs()
{
    float fmSample;
    if(fmods.size() > 0) {
        fmSample = visitFmods();
    }

    if ((dataIndexes.size() < 1) || (useFixedFreq == true)) //no data mappings, use fixed freq
    {
        gen->freq(fixedFreq + fmSample);
    }
    else //map each indexed value from the data row to the freq of a generator
    {
        int idx = dataIndexes[0];
        double freq = dataItem->at(idx);
        if(useFreqScaling)
        {
            freq = scale(freq, mins->at(idx), maxes->at(idx),
                         freqScaleLow, freqScaleHigh, freqScaleExp);
        }
        gen->freq(freq + fmSample);
    }
}

void Modulator::processSetModType(SynthItem::ITEM_CHILD_TYPE modType)
{
    this->modType = modType;
    for(unsigned int i = 0; i < parents.size(); i++)
    {
        SynthItem* parent = parents[i];
        parent->removeChild(this);
        parent->addChild(this, modType);
    }
}

}
