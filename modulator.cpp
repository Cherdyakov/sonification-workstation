#include "modulator.h"

namespace son {

Modulator::Modulator()
{
    my_type_ = ITEM::MODULATOR;
    mod_type_ = PARAMETER::AMPLITUDE;
    muted_ = false;
    depth_ = 100;
    freq_ = 1;
    freq_fixed_ = true;
    freq_scaled_ = true;
    freq_low_ = 40;
    freq_high_ = 16000;

    accepted_children_ = {
        PARAMETER::AMPLITUDE,
        PARAMETER::FREQUENCY
    };

    gen_.freq(freq_);
}

/*
 Functions called from user thread
 */

void Modulator::delete_item()
{
    SynthItemCommand command;
    command.type = COMMAND::DELETE;
    command_buffer_.push(command);
}

SynthItem::ITEM Modulator::get_type()
{
    return my_type_;
}

void Modulator::set_data(std::vector<double> *data, std::vector<double> *mins, std::vector<double> *maxes)
{
    SynthItemCommand command;
    command.type = COMMAND::DATA;
    command.data = data;
    command.mins = mins;
    command.maxes = maxes;
    command_buffer_.push(command);
}

void Modulator::add_parent(SynthItem *parent)
{
    SynthItemCommand command;
    command.type = COMMAND::ADD_PARENT;
    command.item = parent;
    command_buffer_.push(command);
}

void Modulator::remove_parent(SynthItem *parent)
{
    SynthItemCommand command;
    command.type = COMMAND::REMOVE_PARENT;
    command.item = parent;
    command_buffer_.push(command);
}

bool Modulator::add_child(SynthItem *child, SynthItem::PARAMETER param)
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

void Modulator::remove_child(SynthItem *child)
{
    SynthItemCommand command;
    command.type = COMMAND::REMOVE_CHILD;
    command.item = child;
    command_buffer_.push(command);
}

void Modulator::mute(bool mute)
{
    SynthItemCommand command;
    command.type = COMMAND::MUTE;
    command.bool_val = mute;
    command_buffer_.push(command);
}

void Modulator::set_freq(double freq)
{
    SynthItemCommand command;
    command.type = COMMAND::PARAM;
    command.parameter = PARAMETER::FREQUENCY;
    command.doubles.push_back(freq);
    command_buffer_.push(command);
}

void Modulator::set_freq_fixed(bool fixed)
{
    SynthItemCommand command;
    command.type = COMMAND::FIXED;
    command.parameter = PARAMETER::FREQUENCY;
    command.bool_val = fixed;
    command_buffer_.push(command);
}

void Modulator::set_freq_indexes(std::vector<int> indexes)
{
    SynthItemCommand command;
    command.type = COMMAND::INDEXES;
    command.parameter = PARAMETER::FREQUENCY;
    command.ints.assign(indexes.begin(), indexes.end());
    command_buffer_.push(command);
}

void Modulator::set_freq_scaled(bool scaled)
{
    SynthItemCommand command;
    command.type = COMMAND::SCALED;
    command.parameter = PARAMETER::FREQUENCY;
    command.bool_val = scaled;
    command_buffer_.push(command);
}

void Modulator::set_freq_scale_vals(double low, double high, double exp)
{
    SynthItemCommand command;
    command.type = COMMAND::SCALE_VALS;
    command.parameter = PARAMETER::FREQUENCY;
    command.doubles.push_back(low);
    command.doubles.push_back(high);
    command.doubles.push_back(exp);
    command_buffer_.push(command);
}

void Modulator::set_mod_type(PARAMETER param)
{
    SynthItemCommand command;
    command.type = COMMAND::MODULATION;
    command.parameter = param;
    command_buffer_.push(command);
}

void Modulator::set_depth(double depth)
{
    SynthItemCommand command;
    command.type = COMMAND::PARAM;
    command.parameter = PARAMETER::DEPTH;
    command.doubles.push_back(depth);
    command_buffer_.push(command);
}

void Modulator::set_depth_fixed(bool fixed)
{
    SynthItemCommand command;
    command.type = COMMAND::FIXED;
    command.parameter = PARAMETER::DEPTH;
    command.bool_val = fixed;
    command_buffer_.push(command);
}

void Modulator::set_depth_indexes(std::vector<int> indexes)
{
    SynthItemCommand command;
    command.type = COMMAND::INDEXES;
    command.parameter = PARAMETER::DEPTH;
    command.ints.assign(indexes.begin(), indexes.end());
    command_buffer_.push(command);
}

void Modulator::set_depth_scaled(bool scaled)
{
    SynthItemCommand command;
    command.type = COMMAND::SCALED;
    command.parameter = PARAMETER::DEPTH;
    command.bool_val = scaled;
    command_buffer_.push(command);
}

void Modulator::set_depth_scale_vals(double low, double high, double exp)
{
    SynthItemCommand command;
    command.type = COMMAND::SCALE_VALS;
    command.parameter = PARAMETER::DEPTH;
    command.doubles.push_back(low);
    command.doubles.push_back(high);
    command.doubles.push_back(exp);
    command_buffer_.push(command);
}

float Modulator::process()
{
    float sample = 0;

    if(!command_buffer_.empty())
    {
        retrieve_commands();
    }

    if(muted_ || (freq_ == 0 && (freq_fixed_ == true)))
    {
        return 1; // good return value for am and fm
    }

    //set frequency of generator
    set_gen_freq();

    sample = gen_.operator ()();

    //check amods
    if(!amods_.empty())
    {
        float am_sample = visit_children(amods_);
        sample *= am_sample;
    }
    // if we are an fmod, amplify our signal by depth
    if(mod_type_ == PARAMETER::FREQUENCY)
    {
        float depth_sample = get_depth_sample();
        sample *= depth_sample;
    }

    return sample;
}

void Modulator::retrieve_commands()
{
    while(command_buffer_.pop(&current_command_))
    {
        process_command(current_command_);
    }
}

void Modulator::process_command(SynthItemCommand command)
{
    COMMAND type = command.type;

    switch (type) {
    case COMMAND::DATA:
        process_set_data(command.data, command.mins, command.maxes);
        break;
    case COMMAND::MODULATION:
        process_set_mod_type(command.parameter);
        break;
    case COMMAND::ADD_CHILD:
        process_add_child(command.item, command.parameter);
        break;
    case COMMAND::REMOVE_CHILD:
        process_remove_child(command.item);
        break;
    case COMMAND::ADD_PARENT:
        insert_item_unique(command.item, &parents_);
        break;
    case COMMAND::REMOVE_PARENT:
        erase_item(command.item, &parents_);
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

void Modulator::process_add_child(SynthItem *child, SynthItem::PARAMETER parameter)
{
    switch (parameter){
    case PARAMETER::AMPLITUDE:
        insert_item_unique(child, &amods_);
        break;
    case PARAMETER::FREQUENCY:
        insert_item_unique(child, &fmods_);
        break;
    default:
        break; //incompatible child type
    }
    child->add_parent(this);
}

void Modulator::process_remove_child(SynthItem *child)
{
    erase_item(child, &amods_);
    erase_item(child, &fmods_);
}

void Modulator::process_delete_item()
{
    remove_as_child(this, parents_);
    remove_as_parent(this, amods_);
    remove_as_parent(this, fmods_);
    delete this;
}

void Modulator::process_set_data(std::vector<double> *data, std::vector<double>* mins, std::vector<double>* maxes)
{
    data_ = data;
    mins_ = mins;
    maxes_ = maxes;
}

void Modulator::process_set_mod_type(PARAMETER parameter)
{
    mod_type_ = parameter;
    for(unsigned int i = 0; i < parents_.size(); i++)
    {
        SynthItem* parent = parents_[i];
        parent->remove_child(this);
        parent->add_child(this, parameter);
    }
}

void Modulator::process_set_param_value(double val, SynthItem::PARAMETER param)
{
    if(param == PARAMETER::FREQUENCY)
    {
        freq_ = val;
    }
    else if(param == PARAMETER::DEPTH)
    {
        depth_ = val;
    }
}

void Modulator::process_set_param_fixed(bool fixed, SynthItem::PARAMETER param)
{
    if(param == PARAMETER::FREQUENCY)
    {
        freq_fixed_ = fixed;
    }
    else if(param == PARAMETER::DEPTH)
    {
        depth_fixed_ = fixed;
    }
}

void Modulator::process_set_param_indexes(std::vector<int> indexes, PARAMETER param)
{

    if(param == PARAMETER::FREQUENCY)
    {
        freq_indexes_ = indexes;
    }
    else if(param == PARAMETER::DEPTH)
    {
        depth_indexes_ = indexes;
    }
}

void Modulator::process_set_param_scaled(bool scaled, SynthItem::PARAMETER param)
{
    if(param == PARAMETER::FREQUENCY)
    {
        freq_scaled_ = scaled;
    }
    else if(param == PARAMETER::DEPTH)
    {
        depth_scaled_ = scaled;
    }
}

void Modulator::process_set_param_scale_vals(double low, double high, double exp, PARAMETER param)
{
    if(param == PARAMETER::FREQUENCY)
    {
        freq_low_ = low;
        freq_high_ = high;
        freq_exponent_ = exp;
    }
    else if(param == PARAMETER::DEPTH)
    {
        depth_low_ = low;
        depth_high_ = high;
        depth_exponent_ = exp;
    }
}

void Modulator::set_gen_freq()
{
    float fm_sample = 0;
    if(fmods_.size() > 0) {
        fm_sample = visit_children(fmods_);
    }

    if (freq_fixed_ == true || freq_indexes_.size() < 1) //no data mappings, use fixed freq
    {
        gen_.freq(freq_ + fm_sample);
    }
    else //map each indexed value from the data row to the freq of a generator
    {
        double freq = data_->at(freq_indexes_[0]);
        if(freq_scaled_)
        {
            freq = scale(freq, mins_->at(freq_indexes_[0]), maxes_->at(freq_indexes_[0]),
                         freq_low_, freq_high_, freq_exponent_);
        }
        gen_.freq(freq + fm_sample);
    }
}

float Modulator::get_depth_sample()
{
    float depth_sample = 0;
    if (depth_fixed_ == true || depth_indexes_.size() < 1) //no data mappings, use fixed depth_
    {
        depth_sample = depth_;
    }
    else //map indexed value
    {
        depth_sample = data_->at(depth_indexes_[0]);
        if(depth_scaled_)
        {
            depth_sample = scale(depth_sample, mins_->at(depth_indexes_[0]), maxes_->at(depth_indexes_[0]),
                         depth_low_, depth_high_, depth_exponent_);
        }
    }
    return depth_sample;
}

}
