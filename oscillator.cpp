#include "oscillator.h"

namespace son {

Oscillator::Oscillator()
{
    waveform = WAVEFORM::SINE;
    gam::Sine<>* defaultGen = new gam::Sine<>(440);
    gens.push_back(defaultGen);
    freq = 440;
    fixedFreqs = true;
}

void Oscillator::setDataItem(std::vector<double> *data)
{
    SynthItemCommand command;
    command.type = ITEM_COMMAND_TYPE::DATA;
    command.data = data;
    commandBuffer.push(command);
}

void Oscillator::setWaveform(WAVEFORM waveform)
{
    SynthItemCommand command;
    command.type = ITEM_COMMAND_TYPE::WAVEFORM;
    command.waveform = waveform;
    commandBuffer.push(command);
}

void Oscillator::setFreq(double freq)
{
    SynthItemCommand command;
    command.type = ITEM_COMMAND_TYPE::FREQ;
    command.freq = freq;
    commandBuffer.push(command);
}

void Oscillator::setFixedFreqs(bool fixed)
{
    SynthItemCommand command;
    command.type = ITEM_COMMAND_TYPE::FIXED_FREQS;
    command.fixedFreqs = fixed;
    commandBuffer.push(command);
}

void Oscillator::setIndexes(std::vector<int> indexes)
{
    SynthItemCommand command;
    command.type = ITEM_COMMAND_TYPE::INDEXES;
    command.indexes = indexes;
    commandBuffer.push(command);
}

void Oscillator::mute(bool mute)
{
    SynthItemCommand command;
    command.type = ITEM_COMMAND_TYPE::MUTE;
    command.mute = mute;
    commandBuffer.push(command);
}


void Oscillator::addChild(SynthItem *child, SynthItem::CHILD_TYPE type)
{
    SynthItemCommand command;
    command.type = ITEM_COMMAND_TYPE::ADD_CHILD;
    command.item = child;
    command.childType = type;
    commandBuffer.push(command);
}

void Oscillator::removeChild(SynthItem *child)
{
    SynthItemCommand command;
    command.type = ITEM_COMMAND_TYPE::ADD_CHILD;
    command.item = child;
    commandBuffer.push(command);
}

void Oscillator::processAddChild(SynthItem *child, CHILD_TYPE type)
{
    switch (type){
    case CHILD_TYPE::AMOD:
    {
        if(std::find(amods.begin(), amods.end(), child) != amods.end()) {
            return;
        } else {
            amods.push_back(child);
        }
        break;
    }
    case CHILD_TYPE::FMOD:
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
}

void Oscillator::processRemoveChild(SynthItem *child)
{
    amods.erase(std::remove(amods.begin(), amods.end(), child), amods.end());
    fmods.erase(std::remove(fmods.begin(), fmods.end(), child), fmods.end());
}

void Oscillator::processSetDataItem(std::vector<double> *data)
{
    dataItem = data;

    for(unsigned int i = 0; i < amods.size(); i++) {
        son::SynthItem* item = amods[i];
        item->setDataItem(data);
    }
    for(unsigned int i = 0; i < fmods.size(); i++) {
        son::SynthItem* item = fmods[i];
        item->setDataItem(data);
    }
}

void Oscillator::processSetWaveform(WAVEFORM waveType)
{
    resize(0);
    if (waveform != waveType) {
        waveform = waveType;
    }
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

void Oscillator::processSetFreq(double inFreq)
{
    if (freq != inFreq) {
        freq = inFreq;
    }
}

void Oscillator::processSetFixedFreqs(bool fixed)
{
    fixedFreqs = fixed;
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

void Oscillator::processCommand(SynthItemCommand command)
{
    ITEM_COMMAND_TYPE type = command.type;

    switch (type) {
    case ITEM_COMMAND_TYPE::ADD_CHILD:
    {
        processAddChild(command.item, command.childType);
        break;
    }
    case ITEM_COMMAND_TYPE::DATA:
    {
        processSetDataItem(command.data);
        break;
    }
    case ITEM_COMMAND_TYPE::FIXED_FREQS:
    {
        processSetFixedFreqs(command.fixedFreqs);
        break;
    }
    case ITEM_COMMAND_TYPE::FREQ:
    {
        processSetFreq(command.freq);
        break;
    }
    case ITEM_COMMAND_TYPE::INDEXES:
    {
        processSetIndexes(command.indexes);
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
    case ITEM_COMMAND_TYPE::MUTE:
    {
        processMute(command.mute);
        break;
    }
    default:
        break;
    }
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

float Oscillator::process(float in)
{
    return in;
}

float Oscillator::visitAmods()
{
    float s = 0.0;
    for (unsigned int i = 0; i < amods.size(); ++i)
    {
        SynthItem* gen = amods[i];
        s += gen->process();
    }
    return s;
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
    if ((dataIndexes.size() < 1) || (fixedFreqs == true)) //no data mappings, use fixed freq
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

