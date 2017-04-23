#include "oscillator.h"

#include <QDebug>

namespace son {

Oscillator::Oscillator()
{
    myType = ITEM_TYPE::OSCILLATOR;
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

    gam::Sine<>* defaultGen = new gam::Sine<>(fixedFreq);
    gens.push_back(defaultGen);
}

void Oscillator::setWaveform(WAVEFORM waveform)
{
    SynthItemCommand command;
    command.type = ITEM_COMMAND_TYPE::WAVEFORM;
    command.waveform = waveform;
    commandBuffer.push(command);
}

void Oscillator::setFixedFreq(double freq)
{
    SynthItemCommand command;
    command.type = ITEM_COMMAND_TYPE::VALUE;
    command.parameter = ITEM_PARAMETER::FREQUENCY;
    command.doubles.push_back(freq);
    commandBuffer.push(command);
}

void Oscillator::setUseFixedFreq(bool fixed)
{
    SynthItemCommand command;
    command.type = ITEM_COMMAND_TYPE::FIXED;
    command.parameter = ITEM_PARAMETER::FREQUENCY;
    command.boolVal = fixed;
    commandBuffer.push(command);
}

void Oscillator::setUseFreqScaling(bool scaling)
{
    SynthItemCommand command;
    command.type = ITEM_COMMAND_TYPE::SCALING;
    command.parameter = ITEM_PARAMETER::FREQUENCY;
    command.boolVal = scaling;
    commandBuffer.push(command);
}

void Oscillator::setFreqScalingVals(double low, double high, double exp)
{
    SynthItemCommand command;
    command.type = ITEM_COMMAND_TYPE::SCALE_VALS;
    command.parameter = ITEM_PARAMETER::FREQUENCY;
    command.doubles.push_back(low);
    command.doubles.push_back(high);
    command.doubles.push_back(exp);
    commandBuffer.push(command);
}

void Oscillator::setIndexes(std::vector<int> indexes)
{
    SynthItemCommand command;
    command.type = ITEM_COMMAND_TYPE::INDEXES;
    command.parameter = ITEM_PARAMETER::FREQUENCY;
    for(unsigned int i = 0; i < indexes.size(); i++)
    {
        command.ints.push_back(indexes[i]);
    }
    commandBuffer.push(command);
}

void Oscillator::removeChild(SynthItem *child)
{
    SynthItemCommand command;
    command.type = ITEM_COMMAND_TYPE::ADD_CHILD;
    command.item = child;
    commandBuffer.push(command);
}

void Oscillator::processAddChild(SynthItem *child, ITEM_CHILD_TYPE type)
{
    switch (type){
    case ITEM_CHILD_TYPE::AMOD:
    {
        if(std::find(amods.begin(), amods.end(), child) != amods.end()) {
            return;
        } else {
            amods.push_back(child);
        }
        break;
    }
    case ITEM_CHILD_TYPE::FMOD:
    {
        if(std::find(fmods.begin(), fmods.end(), child) != fmods.end()) {
            return;
        } else {
            fmods.push_back(child);
        }
        break;
    }
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

    resize(dataIndexes.size());

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
    ITEM_COMMAND_TYPE type = command.type;

    switch (type) {
    case ITEM_COMMAND_TYPE::ADD_CHILD:
    {
        processAddChild(command.item, command.childType);
        break;
    }
    case ITEM_COMMAND_TYPE::FIXED:
    {
        if(command.parameter == ITEM_PARAMETER::FREQUENCY)
        {
            processSetUseFixedFreq(command.boolVal);
        }
        break;
    }
    case ITEM_COMMAND_TYPE::VALUE:
    {
        if(command.parameter == ITEM_PARAMETER::FREQUENCY)
        {
            processSetFixedFreq(command.doubles[0]);
        }
        break;
    }
    case ITEM_COMMAND_TYPE::INDEXES:
    {
        if(command.parameter == ITEM_PARAMETER::FREQUENCY)
        {
            processSetIndexes(command.ints);
        }
        break;
    }
    case ITEM_COMMAND_TYPE::REMOVE_CHILD:
    {
        processRemoveChild(command.item);
        break;
    }
    case ITEM_COMMAND_TYPE::WAVEFORM:
    {
        processSetWaveform(command.waveform);
        break;
    }
    case ITEM_COMMAND_TYPE::SCALING:
    {
        if(command.parameter == ITEM_PARAMETER::FREQUENCY)
        {
            processSetFreqScaling(command.boolVal);
        }
        break;
    }
    case ITEM_COMMAND_TYPE::SCALE_VALS:
    {
        if(command.parameter == ITEM_PARAMETER::FREQUENCY)
        {
            processSetFreqScalingVals(command.doubles[0],
                                      command.doubles[1],
                                      command.doubles[2]);
        }
        break;
    }
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

    sample /= gens.size();

    //check amods
    if(!amods.empty())
    {
        float amSample = visitAmods();
        sample *= amSample;
    }

    return sample;
}

float Oscillator::process(float in)
{
    return in;
}

float Oscillator::visitFmods()
{
    float s = 0.0;
    for (unsigned int i = 0; i < fmods.size(); ++i)
    {
        SynthItem* gen = fmods[i];
        s += gen->process();
    }
    return s;
}

void Oscillator::setFreqs()
{
    float fmSample = 0;
    if(fmods.size() > 0) {
        fmSample = visitFmods();
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
             (i < dataItem->size()); ++i) {
            int idx = dataIndexes[i];
            double freq = dataItem->at(idx);
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

