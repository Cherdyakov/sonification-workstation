#include "oscillator.h"

namespace son {

Oscillator::Oscillator()
{
    waveform = SON_WAVEFORM::SINE;
    gam::Sine<>* defaultGen = new gam::Sine<>(440);
    gens.push_back(defaultGen);
    freq = 440;
    fixedFreqs = true;
}

void Oscillator::setDataItem(std::vector<double> *data)
{
    OscillatorCommand command;
    command.type = SON_OSC_COMMAND_TYPE::DATA;
    command.data = data;
    commandBuffer.push(command);
}

void Oscillator::setWaveform(SON_WAVEFORM waveform)
{
    OscillatorCommand command;
    command.type = SON_OSC_COMMAND_TYPE::WAVEFORM;
    command.waveform = waveform;
    commandBuffer.push(command);
}

void Oscillator::setFreq(double freq)
{
    OscillatorCommand command;
    command.type = SON_OSC_COMMAND_TYPE::FREQ;
    command.freq = freq;
    commandBuffer.push(command);
}

void Oscillator::setFixedFreqs(bool fixed)
{
    OscillatorCommand command;
    command.type = SON_OSC_COMMAND_TYPE::FIXED_FREQS;
    command.fixedFreqs = fixed;
    commandBuffer.push(command);
}

void Oscillator::setIndexes(std::vector<int> indexes)
{
    OscillatorCommand command;
    command.type = SON_OSC_COMMAND_TYPE::INDEXES;
    command.indexes = indexes;
    commandBuffer.push(command);
}

void Oscillator::processAddChild(SynthItem *child, SON_CHILD_TYPE type)
{
    SynthItem* item = static_cast<SynthItem*>(child);

    switch (type){
    case SON_CHILD_TYPE::AMOD:
    {
        if(std::find(amods.begin(), amods.end(), item) != amods.end()) {
            return;
        } else {
            amods.push_back(item);
        }
        break;
    }
    case SON_CHILD_TYPE::FMOD:
    {
        if(std::find(fmods.begin(), fmods.end(), item) != fmods.end()) {
            return;
        } else {
            fmods.push_back(item);
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

void Oscillator::processSetWaveform(SON_WAVEFORM waveType)
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

void Oscillator::processCommand(OscillatorCommand command)
{
    SON_OSC_COMMAND_TYPE type = command.type;

    switch (type) {
    case SON_OSC_COMMAND_TYPE::ADD_CHILD:
    {
        SynthItem* child = command.child;
        SON_CHILD_TYPE type = command.childType;
        processAddChild(child, type);
    }
        break;
    case SON_OSC_COMMAND_TYPE::DATA:
    {
        std::vector<double>* data = command.data;
        processSetDataItem(data);
    }
        break;
    case SON_OSC_COMMAND_TYPE::FIXED_FREQS:
    {
        bool fixedFreqs = command.fixedFreqs;
        processSetFixedFreqs(fixedFreqs);
    }
        break;
    case SON_OSC_COMMAND_TYPE::FREQ:
    {
        double freq = command.freq;
        processSetFreq(freq);
    }
        break;
    case SON_OSC_COMMAND_TYPE::INDEXES:
    {

    }
        break;
    case SON_OSC_COMMAND_TYPE::REMOVE_CHILD:
    {

    }
        break;
    case SON_OSC_COMMAND_TYPE::WAVEFORM:
    {

    }
        break;

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

gam::AccumPhase<> *Oscillator::newGen(SON_WAVEFORM type)
{
    switch (type) {
    case SON_WAVEFORM::SINE:
        return new gam::Sine<>(440);
        break;
    case SON_WAVEFORM::SAW:
        return new gam::Saw<>(440);
        break;
    case SON_WAVEFORM::SQUARE:
        return new gam::Square<>(440);
    default:
        return NULL;
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
    for (unsigned int i = 0; i < gens.size(); ++i) {

        switch (waveform) {
        case SON_WAVEFORM::SINE:
        {
            gam::Sine<>* gen = static_cast<gam::Sine<>*>(gens[i]);
            sample += gen->operator ()();
            break;
        }
        case SON_WAVEFORM::SAW:
        {
            gam::Saw<>* gen = static_cast<gam::Saw<>*>(gens[i]);
            sample += gen->operator ()();
            break;
        }
        case SON_WAVEFORM::SQUARE:
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

    return sample / gens.size();
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

