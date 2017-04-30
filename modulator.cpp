#include "modulator.h"

namespace son {

Modulator::Modulator()
{
    myType = ITEM::MODULATOR;
    modType = PARAMETER::AMPLITUDE;
    waveform = WAVEFORM::SINE;
    depth = 100;
    frequency_ = 1;
    frequency_fixed_ = true;
    freq_scaled = true;
    freq_low_ = 40;
    freq_high_ = 16000;

    acceptedChildren = {
        PARAMETER::AMPLITUDE,
        PARAMETER::FREQUENCY
    };

    gen = new gam::Sine<>(frequency_);
}

float Modulator::process()
{
    float sample = 0;

    if(!commandBuffer.empty())
    {
        retrieve_commands();
    }

    if(muted || (frequency_ == 0 && (frequency_fixed_ == true)))
    {
        return 1; // good return value for am and fm
    }

    //set frequency of generator
    set_gen_freqs();

    gam::Sine<>* g = dynamic_cast<gam::Sine<>*>(gen);

    //generate sample
    switch (waveform) {
    case WAVEFORM::SINE:
        sample += g->operator ()();
        break;
    case WAVEFORM::SAW:
        sample += g->operator ()();
        break;
    case WAVEFORM::SQUARE:
        sample += g->operator ()();
        break;
    default:
        break;
    }

    //check amods
    if(!amods.empty())
    {
        float amSample = visitChildren(amods);
        sample *= amSample;
    }
    if(modType == PARAMETER::FREQUENCY)
    {
        sample *= depth;
    }

    return sample;
}

void Modulator::setModulationType(PARAMETER parameter)
{
    SynthItemCommand command;
    command.type = COMMAND::MODULATION;
    command.parameter = parameter;
    commandBuffer.push(command);
}

void Modulator::setDepth(double depth)
{
    SynthItemCommand command;
    command.type = COMMAND::PARAM;
    command.parameter = PARAMETER::DEPTH;
    command.doubles.push_back(depth);
    commandBuffer.push(command);
}

void Modulator::setUseFixedDepth(bool fixed)
{
    SynthItemCommand command;
    command.type = COMMAND::FIXED;
    command.parameter = PARAMETER::DEPTH;
    command.boolVal = fixed;
    commandBuffer.push(command);
}

void Modulator::setUseDepthScaling(bool scaling)
{
    SynthItemCommand command;
    command.type = COMMAND::SCALING;
    command.parameter = PARAMETER::DEPTH;
    command.boolVal = scaling;
    commandBuffer.push(command);
}

void Modulator::setDepthScalingVals(double low, double high, double exp)
{
    SynthItemCommand command;
    command.type = COMMAND::SCALE_VALS;
    command.parameter = PARAMETER::DEPTH;
    command.doubles.push_back(low);
    command.doubles.push_back(high);
    command.doubles.push_back(exp);
    commandBuffer.push(command);
}

void Modulator::process_command(SynthItemCommand command)
{
    COMMAND type = command.type;

    switch (type) {
    case COMMAND::PARAM:
        switch (command.parameter) {
        case PARAMETER::DEPTH:
            processSetDepth(command.doubles[0]);
            break;
        default:
            Oscillator::process_command(command);
            break;
        }
        break;
    case COMMAND::MODULATION:
        processSetModType(command.parameter);
        break;
    default:
        Oscillator::process_command(command);
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

void Modulator::processSetDepth(double depth)
{
    this->depth = depth;
}

void Modulator::processSetUseFixedDepth(bool fixed)
{
    useFixedDepth = fixed;
}

void Modulator::processSetUseDepthScaling(bool scaling)
{
    useDepthScaling = scaling;
}

void Modulator::processSetDepthScalingVals(double low, double high, double exp)
{
    depthScaleLow = low;
    depthScaleHigh = high;
    depthScaleExp = exp;
}

void Modulator::set_gen_freqs()
{
    float fmSample = 0;;
    if(fmods_.size() > 0) {
        fmSample = visitChildren(fmods_);
    }

    if ((freq_indexes_.size() < 1) || (frequency_fixed_ == true)) //no data mappings, use fixed freq
    {
        gen->freq(frequency_ + fmSample);
    }
    else //map each indexed value from the data row to the freq of a generator
    {
        int idx = freq_indexes_[0];
        double freq = data->at(idx);
        if(freq_scaled)
        {
            freq = scale(freq, mins->at(idx), maxes->at(idx),
                         freq_low_, freq_high_, freq_exponent);
        }
        gen->freq(freq + fmSample);
    }
}

void Modulator::processSetModType(PARAMETER parameter)
{
    modType = parameter;
    for(unsigned int i = 0; i < parents.size(); i++)
    {
        SynthItem* parent = parents[i];
        parent->remove_child(this);
        parent->add_child(this, parameter);
    }
}

}
