#include "oscillator.h"

#include <QDebug>

namespace son {

Oscillator::Oscillator()
{
    my_type_ = ITEM::OSCILLATOR;
    freq_ = 440;
    freq_fixed_ = true;
    freq_scaled_ = true;
    freq_low_ = 40;
    freq_high_ = 16000;
    freq_exponent_ = 1;

    accepted_children_ = {
        PARAMETER::AMPLITUDE,
        PARAMETER::FREQUENCY
    };

}

Oscillator::~Oscillator()
{

}

/*
 Functions called from user thread
 */

void Oscillator::delete_item()
{
    SynthItemCommand command;
    command.type = COMMAND::DELETE;
    command_buffer_.push(command);
}

SynthItem::ITEM Oscillator::get_type()
{
    return my_type_;
}

void Oscillator::set_data(std::vector<double> *data, std::vector<double> mins, std::vector<double> maxes)
{
    SynthItemCommand command;
    command.type = COMMAND::DATA;
    command.data = data;
    command.mins = mins;
    command.maxes = maxes;
    command_buffer_.push(command);
}

void Oscillator::add_parent(SynthItem *parent)
{
    SynthItemCommand command;
    command.type = COMMAND::ADD_PARENT;
    command.item = parent;
    command_buffer_.push(command);
}

void Oscillator::remove_parent(SynthItem *parent)
{
    SynthItemCommand command;
    command.type = COMMAND::REMOVE_PARENT;
    command.item = parent;
    command_buffer_.push(command);
}

bool Oscillator::add_child(SynthItem *child, SynthItem::PARAMETER param)
{
    if(!verify_child(param, accepted_children_))
    {
        return false;
    }
    SynthItemCommand command;
    command.type = COMMAND::ADD_CHILD;
    command.parameter = param;
    command.item = child;
    command_buffer_.push(command);
    return true;
}

void Oscillator::remove_child(SynthItem *child)
{
    SynthItemCommand command;
    command.type = COMMAND::REMOVE_CHILD;
    command.item = child;
    command_buffer_.push(command);
}

void Oscillator::mute(bool mute)
{
    SynthItemCommand command;
    command.type = COMMAND::MUTE;
    command.bool_val = mute;
    command_buffer_.push(command);
}

void Oscillator::set_freq(double frequency)
{
    SynthItemCommand command;
    command.type = COMMAND::PARAM;
    command.parameter = PARAMETER::FREQUENCY;
    command.doubles.push_back(frequency);
    command_buffer_.push(command);
}

void Oscillator::set_freq_fixed(bool fixed)
{
    SynthItemCommand command;
    command.type = COMMAND::FIXED;
    command.parameter = PARAMETER::FREQUENCY;
    command.bool_val = fixed;
    command_buffer_.push(command);
}

void Oscillator::set_freq_indexes(std::vector<int> indexes)
{
    SynthItemCommand command;
    command.type = COMMAND::INDEXES;
    command.parameter = PARAMETER::FREQUENCY;
    command.ints.assign(indexes.begin(), indexes.end());
    command_buffer_.push(command);
}

void Oscillator::set_freq_scaled(bool scaled)
{
    SynthItemCommand command;
    command.type = COMMAND::SCALED;
    command.parameter = PARAMETER::FREQUENCY;
    command.bool_val = scaled;
    command_buffer_.push(command);
}

void Oscillator::set_freq_scale_vals(double low, double high, double exp)
{
    SynthItemCommand command;
    command.type = COMMAND::SCALE_VALS;
    command.parameter = PARAMETER::FREQUENCY;
    command.doubles.push_back(low);
    command.doubles.push_back(high);
    command.doubles.push_back(exp);
    command_buffer_.push(command);
}

/*
 Functions called from audio callback thread
 */

float Oscillator::process()
{
    float sample = 0.0;

    if(!command_buffer_.empty())
    {
        retrieve_commands();
    }

    if(muted_)
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
        sample += gens_[i]();
    }

    sample /= gens_.size();

    // vist amplitude modulating children
    if(!amods_.empty())
    {
        float am_sample = visit_children(amods_);
        sample *= am_sample;
    }

    return sample;
}

void Oscillator::retrieve_commands()
{
    while(command_buffer_.pop(&current_command_))
    {
        process_command(current_command_);
    }
}

void Oscillator::process_command(SynthItemCommand command)
{
    COMMAND type = command.type;

    switch (type) {
    case COMMAND::DATA:
        process_set_data(command.data, command.mins, command.maxes);
        break;
    case COMMAND::ADD_CHILD:
        process_add_child(command.item, command.parameter);
        break;
    case COMMAND::REMOVE_CHILD:
        process_remove_child(command.item);
        break;
    case COMMAND::ADD_PARENT:
        insert_item_unique(command.item, parents_);
        break;
    case COMMAND::REMOVE_PARENT:
        erase_item(command.item, parents_);
        break;
    case COMMAND::MUTE:
        muted_ = command.bool_val;
        break;
    case COMMAND::PARAM:
        process_set_param_value(command.doubles[0], command.parameter);
        break;
    case COMMAND::FIXED:
        process_set_param_fixed(command.bool_val, command.parameter);
        break;
    case COMMAND::INDEXES:
        process_set_param_indexes(command.ints, command.parameter);
        break;
    case COMMAND::SCALED:
        process_set_param_scaled(command.bool_val, command.parameter);
        break;
    case COMMAND::SCALE_VALS:
        process_set_param_scale_vals(command.doubles[0], command.doubles[1], command.doubles[2], command.parameter);
        break;
    case COMMAND::DELETE:
        process_delete_item();
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
    erase_item(child, amods_);
    erase_item(child, fmods_);
}

void Oscillator::process_delete_item()
{
    remove_as_child(this, parents_);
    remove_as_parent(this, amods_);
    remove_as_parent(this, fmods_);
    delete this;
}

void Oscillator::process_set_data(std::vector<double> *data, std::vector<double> mins, std::vector<double> maxes)
{
    data_ = data;
    mins_ = mins;
    maxes_ = maxes;
}

void Oscillator::process_set_param_value(double val, SynthItem::PARAMETER param)
{
    if(param == PARAMETER::FREQUENCY)
    {
        freq_ = val;
    }
}

void Oscillator::process_set_param_fixed(bool fixed, SynthItem::PARAMETER param)
{
    if(param == PARAMETER::FREQUENCY)
    {
        freq_fixed_ = fixed;
    }
}

void Oscillator::process_set_param_indexes(std::vector<int> indexes, SynthItem::PARAMETER param)
{
    if(param == PARAMETER::FREQUENCY)
    {
        freq_indexes_ = indexes;
    }
}

void Oscillator::process_set_param_scaled(bool scaled, SynthItem::PARAMETER param)
{
    if(param == PARAMETER::FREQUENCY)
    {
        freq_scaled_ = scaled;
    }
}

void Oscillator::process_set_param_scale_vals(double low, double high, double exp, SynthItem::PARAMETER param)
{
    if(param == PARAMETER::FREQUENCY)
    {
        freq_low_ = low;
        freq_high_ = high;
        freq_exponent_ = exp;
    }
}

void Oscillator::set_gen_freqs()
{
    float fm_sample = 0;
    if(fmods_.size() > 0) {
        fm_sample = visit_children(fmods_);
    }

    if (freq_fixed_ == true || freq_indexes_.size() < 1) //no data mappings, use fixed freq
    {
        gens_[0].freq(freq_ + fm_sample);
    }
    else //map each indexed value from the data row to the freq of a generator
    {
        for (unsigned int i = 0; i < freq_indexes_.size(); ++i) {
            int idx = freq_indexes_[i];
            double freq = data_->at(idx);
            if(freq_scaled_)
            {
                freq = scale(freq, mins_.at(idx), maxes_.at(idx),
                             freq_low_, freq_high_, freq_exponent_);
            }
            gens_[i].freq(freq + fm_sample);
        }
    }
}

}
