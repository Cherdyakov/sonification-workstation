#include "oscillator.h"

#include <QDebug>

namespace son {

Oscillator::Oscillator()
{
    myType = ITEM::OSCILLATOR;
    frequency_ = 440;
    frequency_fixed_ = true;
    freq_scaled = true;
    freq_low_ = 40;
    freq_high_ = 16000;
    freq_exponent = 1;
    current_size_ = 1;

    acceptedChildren = {
        PARAMETER::AMPLITUDE,
        PARAMETER::FREQUENCY
    };

    for(int i = 0; i < MAX_DIMENSIONS; i++)
    {
        gam::Sine<>* gen = new gam::Sine<>(frequency_);
        gens_.push_back(gen);
    }
}

Oscillator::~Oscillator()
{
    for(unsigned int i = 0; i < gens_.size(); i++)
    {
        gam::Sine<>* gen = gens_[i];
        delete gen;
    }
}

/*
 Functions called from user thread
 */

void Oscillator::delete_item()
{
    SynthItemCommand command;
    command.type = COMMAND::DELETE;
    commandBuffer.push(command);
}

void Oscillator::set_data(std::vector<double> *data, std::vector<double> mins, std::vector<double> maxes)
{
    SynthItemCommand command;
    command.type = COMMAND::DATA;
    command.data_ = data;
    command.mins_ = mins;
    command.maxes = maxes;
    commandBuffer.push(command);
}

void Oscillator::add_parent(SynthItem *parent)
{

}

void Oscillator::remove_parent(SynthItem *parent)
{

}

bool Oscillator::add_child(SynthItem *child, SynthItem::PARAMETER parameter)
{

}

void Oscillator::remove_child(SynthItem *child)
{
    SynthItemCommand command;
    command.type = COMMAND::REMOVE_CHILD;
    command.item = child;
    commandBuffer.push(command);
}

void Oscillator::set_freq(double frequency)
{
    SynthItemCommand command;
    command.type = COMMAND::PARAM;
    command.parameter = PARAMETER::FREQUENCY;
    command.doubles.push_back(frequency);
    commandBuffer.push(command);
}

void Oscillator::set_freq_indexes(std::vector<int> indexes)
{
    SynthItemCommand command;
    command.type = COMMAND::INDEXES;
    command.parameter = PARAMETER::FREQUENCY;
    for (unsigned int i = 0; i < indexes.size(); i++) {
        command.ints.push_back(indexes[i]);
    }
    commandBuffer.push(command);
}

void Oscillator::set_freq_fixed(bool fixed)
{
    SynthItemCommand command;
    command.type = COMMAND::FIXED;
    command.parameter = PARAMETER::FREQUENCY;
    command.boolVal = fixed;
    commandBuffer.push(command);
}

void Oscillator::set_freq_scaled(bool scaled)
{
    SynthItemCommand command;
    command.type = COMMAND::SCALING;
    command.parameter = PARAMETER::FREQUENCY;
    command.boolVal = scaled;
    commandBuffer.push(command);
}

void Oscillator::set_freq_scale_vals(double low, double high, double exp)
{
    SynthItemCommand command;
    command.type = COMMAND::SCALE_VALS;
    command.parameter = PARAMETER::FREQUENCY;
    command.doubles.push_back(low);
    command.doubles.push_back(high);
    command.doubles.push_back(exp);
    commandBuffer.push(command);
}

/*
 Functions called from audio callback thread
 */

float Oscillator::process()
{
    float sample = 0.0;

    if(!commandBuffer.empty())
    {
        retrieve_commands();
    }

    if(muted)
    {
        return sample;
    }

    //set frequencies of generators
    set_gen_freqs();

    //generate sample
    unsigned int size = freq_indexes_.size();
    if(size < 1)
    {
        size = 1;
    }
    for (unsigned int i = 0; i < size; ++i) {
        sample += gens_[i].process();
    }

    sample /= gens_.size();

    // vist amplitude modulating children
    if(!amods.empty())
    {
        float amSample = visitChildren(amods);
        sample *= amSample;
    }

    return sample;
}

void Oscillator::process_set_freq(double fixedFreq)
{
    if (this->frequency_ != fixedFreq) {
        this->frequency_ = fixedFreq;
    }
}

void Oscillator::process_set_fixed_freq(bool useFixedFreq)
{
    this->frequency_fixed_ = useFixedFreq;
}

void Oscillator::process_set_freq_indexes(std::vector<int> indexes)
{
    bool m = muted;
    if(!muted) {
        muted = true;
    }
    freq_indexes_ = indexes;

    current_size_ = freq_indexes_.size();
    if(current_size_ < 1)
    {
        current_size_ = 1;
    }

    muted = m;
}

void Oscillator::process_set_scale_freq(bool useFreqScaling)
{
    this->freq_scaled = useFreqScaling;
}

void Oscillator::process_set_freq_scale_vals(double low, double high, double exp)
{
    qDebug() << "cpp scalingVals: " << low << " " << high << " " << exp;
    freq_low_ = low;
    freq_high_ = high;
    freq_exponent = exp;
}

void Oscillator::process_command(SynthItemCommand command)
{
    COMMAND type = command.type;

    switch (type) {
    case COMMAND::FIXED:
        if(command.parameter == PARAMETER::FREQUENCY)
        {
            process_set_fixed_freq(command.boolVal);
        }
        break;
    case COMMAND::PARAM:
        if(command.parameter == PARAMETER::FREQUENCY)
        {
            process_set_freq(command.doubles[0]);
        }
        break;
    case COMMAND::INDEXES:
        if(command.parameter == PARAMETER::FREQUENCY)
        {
            process_set_freq_indexes(command.ints);
        }
        break;
    case COMMAND::SCALING:
        if(command.parameter == PARAMETER::FREQUENCY)
        {
            process_set_scale_freq(command.boolVal);
        }
        break;
    case COMMAND::SCALE_VALS:
        if(command.parameter == PARAMETER::FREQUENCY)
        {
            process_set_freq_scale_vals(command.doubles[0], command.doubles[1], command.doubles[2]);
        }
        break;
    default:
        break;
    }
}

void Oscillator::process_add_child(SynthItem *child, PARAMETER parameter)
{
    switch (parameter){
    case PARAMETER::AMPLITUDE:
        insert_item_unique(child, amods_);
        break;
    case PARAMETER::FREQUENCY:
        insert_item_unique(child, fmods_);
        break;
    default:
        break; //incompatible child type
    }
    child->add_parent(this);
}

void Oscillator::process_remove_child(SynthItem *child)
{
    amods.erase(std::remove(amods.begin(), amods.end(), child), amods.end());
    fmods_.erase(std::remove(fmods_.begin(), fmods_.end(), child), fmods_.end());
}

void Oscillator::process_add_parent(SynthItem *parent)
{
    insert_item_unique(parent, parents_);
}

void Oscillator::process_remove_parent(SynthItem *parent)
{
    parents.erase(std::remove(parents.begin(), parents.end(), parent), parents.end());
}

void Oscillator::process_delete_item()
{
    muted = true;

    for(unsigned int i = 0; i < parents.size(); i++) {
        SynthItem* parent = parents[i];
        parent->remove_child(this);
    }
    for(unsigned int i = 0; i < amods.size(); i++) {
        SynthItem* child = amods[i];
        child->remove_parent(this);
    }
    for(unsigned int i = 0; i < fmods_.size(); i++) {
        SynthItem* child = fmods_[i];
        child->remove_parent(this);
    }

    delete this;
}

void Oscillator::set_gen_freqs()
{
    float fmSample = 0;
    if(fmods_.size() > 0) {
        fmSample = visitChildren(fmods_);
    }

    if (frequency_fixed_ == true || freq_indexes_.size() < 1) //no data mappings, use fixed freq
    {
        gens_[i]->freq(frequency_ + fmSample);
    }
    else //map each indexed value from the data row to the freq of a generator
    {
        for (unsigned int i = 0; i < freq_indexes_.size(); ++i) {
            int idx = freq_indexes_[i];
            double freq = data->at(idx);
            if(freq_scaled)
            {
                freq = scale(freq, mins->at(idx), maxes->at(idx),
                             freq_low_, freq_high_, freq_exponent);
            }
            gens_[i]->freq(freq + fmSample);
        }
    }
}

}
