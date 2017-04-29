#include "oscillator.h"

#include <QDebug>

namespace son {

Oscillator::Oscillator()
{
    myType = ITEM::OSCILLATOR;
    waveform = WAVEFORM::SINE;
    fixedFreq = 440;
    useFixedFreq = true;
    useFreqScaling = true;
    freqScaleLow = 40;
    freqScaleHigh = 16000;
    freqScaleExp = 1;

    acceptedChildren = {
        PARAMETER::AMPLITUDE,
        PARAMETER::FREQUENCY
    };

    gam::Sine<>* defaultGen = new gam::Sine<>(fixedFreq);
    gens.push_back(defaultGen);
}

void Oscillator::setWaveform(WAVEFORM waveform)
{
    SynthItemCommand command;
    command.type = COMMAND::WAVEFORM;
    command.waveform = waveform;
    commandBuffer.push(command);
}

void Oscillator::setFixedFreq(double freq)
{
    SynthItemCommand command;
    command.type = COMMAND::PARAM;
    command.parameter = PARAMETER::FREQUENCY;
    command.doubles.push_back(freq);
    commandBuffer.push(command);
}

void Oscillator::setUseFixedFreq(bool fixed)
{
    SynthItemCommand command;
    command.type = COMMAND::FIXED;
    command.parameter = PARAMETER::FREQUENCY;
    command.boolVal = fixed;
    commandBuffer.push(command);
}

void Oscillator::setUseFreqScaling(bool scaling)
{
    SynthItemCommand command;
    command.type = COMMAND::SCALING;
    command.parameter = PARAMETER::FREQUENCY;
    command.boolVal = scaling;
    commandBuffer.push(command);
}

void Oscillator::setFreqScalingVals(double low, double high, double exp)
{
    SynthItemCommand command;
    command.type = COMMAND::SCALE_VALS;
    command.parameter = PARAMETER::FREQUENCY;
    command.doubles.push_back(low);
    command.doubles.push_back(high);
    command.doubles.push_back(exp);
    commandBuffer.push(command);
}

void Oscillator::processDeleteItem()
{
    muted = true;

    for(unsigned int i = 0; i < parents.size(); i++) {
        SynthItem* parent = parents[i];
        parent->removeChild(this);
    }
    for(unsigned int i = 0; i < amods.size(); i++) {
        SynthItem* child = amods[i];
        child->removeParent(this);
    }
    for(unsigned int i = 0; i < fmods.size(); i++) {
        SynthItem* child = fmods[i];
        child->removeParent(this);
    }

    delete this;
}

void Oscillator::removeChild(SynthItem *child)
{
    SynthItemCommand command;
    command.type = COMMAND::REMOVE_CHILD;
    command.item = child;
    commandBuffer.push(command);
}

void Oscillator::processAddChild(SynthItem *child, PARAMETER parameter)
{
    switch (parameter){
    case PARAMETER::AMPLITUDE:
        if(std::find(amods.begin(), amods.end(), child) != amods.end()) {
            return;
        } else {
            amods.push_back(child);
        }
        break;
    case PARAMETER::FREQUENCY:
        if(std::find(fmods.begin(), fmods.end(), child) != fmods.end()) {
            return;
        } else {
            fmods.push_back(child);
        }
        break;
    default:
        break; //incompatible child type
    }
    child->addParent(this);
}

void Oscillator::processRemoveChild(SynthItem *child)
{
    amods.erase(std::remove(amods.begin(), amods.end(), child), amods.end());
    fmods.erase(std::remove(fmods.begin(), fmods.end(), child), fmods.end());
}

void Oscillator::processSetWaveform(WAVEFORM waveType)
{
    if (waveform != waveType) {
        resize(0);
        waveform = waveType;
        // Data mappings exist, resize to fit them
        if(dataIndexes.size() > 0)
        {
            resize(dataIndexes.size());
        }
        else // No data mappings, just default oscillator
        {
            resize(1);
        }
    }
}

void Oscillator::processSetFixedFreq(double fixedFreq)
{
    if (this->fixedFreq != fixedFreq) {
        this->fixedFreq = fixedFreq;
    }
}

void Oscillator::processSetUseFixedFreq(bool useFixedFreq)
{
    this->useFixedFreq = useFixedFreq;
}

void Oscillator::processSetIndexes(std::vector<int> indexes)
{
    bool m = muted;
    if(!muted) {
        muted = true;
    }
    dataIndexes = indexes;

    if(dataIndexes.size() > 0) {
        resize(dataIndexes.size());
    }

    muted = m;
}

void Oscillator::processSetFreqScaling(bool useFreqScaling)
{
    this->useFreqScaling = useFreqScaling;
}

void Oscillator::processSetFreqScalingVals(double low, double high, double exp)
{
    qDebug() << "cpp scalingVals: " << low << " " << high << " " << exp;
    freqScaleLow = low;
    freqScaleHigh = high;
    freqScaleExp = exp;
}

void Oscillator::processCommand(SynthItemCommand command)
{
    COMMAND type = command.type;

    switch (type) {
    case COMMAND::FIXED:
        if(command.parameter == PARAMETER::FREQUENCY)
        {
            processSetUseFixedFreq(command.boolVal);
        }
        else
        {
            SynthItem::processCommand(command);
        }
        break;
    case COMMAND::PARAM:
        if(command.parameter == PARAMETER::FREQUENCY)
        {
            processSetFixedFreq(command.doubles[0]);
        }
        else
        {
            SynthItem::processCommand(command);
        }
        break;
    case COMMAND::INDEXES:
        if(command.parameter == PARAMETER::FREQUENCY)
        {
            processSetIndexes(command.ints);
        }
        else
        {
            SynthItem::processCommand(command);
        }
        break;
    case COMMAND::WAVEFORM:
        processSetWaveform(command.waveform);
        break;
    case COMMAND::SCALING:
        if(command.parameter == PARAMETER::FREQUENCY)
        {
            processSetFreqScaling(command.boolVal);
        }
        else
        {
            SynthItem::processCommand(command);
        }
        break;
    case COMMAND::SCALE_VALS:
        if(command.parameter == PARAMETER::FREQUENCY)
        {
            processSetFreqScalingVals(command.doubles[0],
                    command.doubles[1],
                    command.doubles[2]);
        }
        else
        {
            SynthItem::processCommand(command);
        }
        break;
    default:
        SynthItem::processCommand(command);
        break;
    }
}

void Oscillator::resize(unsigned int size)
{
    bool wasMuted = muted;
    if(!muted) {
        muted = true;
    }

    while(gens.size() < size)
    {
        gens.push_back(newGen(waveform));
    }
    while(gens.size() > size)
    {
        gam::AccumPhase<>* gen = gens[gens.size() - 1];
        gens.pop_back();
        delete gen;
    }

    muted = wasMuted;

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

    //set frequencies of generators
    setFreqs();

    //generate sample
    for (unsigned int i = 0; i < gens.size(); ++i) {


        gam::Sine<>* gen = static_cast<gam::Sine<>*>(gens[i]);

        switch (waveform) {
        case WAVEFORM::SINE:
            sample += gen->operator ()();
            break;
        case WAVEFORM::SAW:
            sample += gen->operator ()();
            break;
        case WAVEFORM::SQUARE:
            sample += gen->operator ()();
            break;
        default:
            break;
        }
    }

    sample /= gens.size();

    // vist amplitude modulating children
    if(!amods.empty())
    {
        float amSample = visitChildren(amods);
        sample *= amSample;
    }

    return sample;
}

void Oscillator::setFreqs()
{
    float fmSample = 0;
    if(fmods.size() > 0) {
        fmSample = visitChildren(fmods);
    }

    if ((dataIndexes.size() < 1) || (useFixedFreq == true)) //no data mappings, use fixed freq
    {
        for (unsigned int i = 0; i < gens.size(); ++i) {
            gens[i]->freq(fixedFreq + fmSample);
        }
    }
    else //map each indexed value from the data row to the freq of a generator
    {
        for (unsigned int i = 0; (i < gens.size()) &&
             (i < dataIndexes.size()) &&
             (i < data->size()); ++i) {
            int idx = dataIndexes[i];
            double freq = data->at(idx);
            if(useFreqScaling)
            {
                freq = scale(freq, mins->at(idx), maxes->at(idx),
                             freqScaleLow, freqScaleHigh, freqScaleExp);
            }
            gens[i]->freq(freq + fmSample);
        }
    }

}

}

