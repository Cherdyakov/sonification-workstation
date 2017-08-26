#include "modulator.h"

namespace son {

Modulator::Modulator()
{
    my_type_ = ITEM::MODULATOR;
    child_type_ = PARAMETER::AMPLITUDE;
    muted_ = false;

    // freq
    freq_ = 1;
    freq_fixed_ = true;
    freq_scaled_ = true;
    freq_low_ = 40;
    freq_high_ = 16000;
    freq_exponent_ = 1;

    // depth
    depth_ = 100;
    depth_fixed_ = true;
    depth_scaled_ = true;
    depth_low_ = 40;
    depth_high_ = 16000;
    depth_exponent_ = 1;

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

bool Modulator::add_child(SynthItem *child, PARAMETER param)
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

void Modulator::set_freq_scale_low(double low)
{
    SynthItemCommand command;
    command.type = COMMAND::SCALE_LOW;
    command.parameter = PARAMETER::FREQUENCY;
    command.doubles.push_back(low);
    command_buffer_.push(command);
}

void Modulator::set_freq_scale_high(double high)
{
    SynthItemCommand command;
    command.type = COMMAND::SCALE_HIGH;
    command.parameter = PARAMETER::FREQUENCY;
    command.doubles.push_back(high);
    command_buffer_.push(command);
}

void Modulator::set_freq_scale_exponent(double exponent)
{
    SynthItemCommand command;
    command.type = COMMAND::SCALE_EXPONENT;
    command.parameter = PARAMETER::FREQUENCY;
    command.doubles.push_back(exponent);
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

void Modulator::set_depth_scale_low(double low)
{
    SynthItemCommand command;
    command.type = COMMAND::SCALE_LOW;
    command.parameter = PARAMETER::FREQUENCY;
    command.doubles.push_back(low);
    command_buffer_.push(command);
}

void Modulator::set_depth_scale_high(double high)
{
    SynthItemCommand command;
    command.type = COMMAND::SCALE_HIGH;
    command.parameter = PARAMETER::FREQUENCY;
    command.doubles.push_back(high);
    command_buffer_.push(command);
}

void Modulator::set_depth_scale_exponent(double exponent)
{
    SynthItemCommand command;
    command.type = COMMAND::SCALE_EXPONENT;
    command.parameter = PARAMETER::FREQUENCY;
    command.doubles.push_back(exponent);
    command_buffer_.push(command);
}

bool Modulator::get_mute()
{
    return muted_;
}

std::vector<SynthItem *> Modulator::get_parents()
{
    return parents_;
}

double Modulator::get_freq()
{
    return freq_;
}

bool Modulator::get_freq_fixed()
{
    return freq_fixed_;
}

std::vector<int> Modulator::get_freq_indexes()
{
    return freq_indexes_;
}

bool Modulator::get_freq_scaled()
{
    return freq_scaled_;
}

double Modulator::get_freq_scale_low()
{
    return freq_low_;
}

double Modulator::get_freq_scale_high()
{
    return freq_high_;
}

double Modulator::get_freq_scale_exponent()
{
    return freq_exponent_;
}

double Modulator::get_depth()
{
    return depth_;
}

bool Modulator::get_depth_fixed()
{
    return depth_fixed_;
}

std::vector<int> Modulator::get_depth_indexes()
{
    return depth_indexes_;
}

bool Modulator::get_depth_scaled()
{
    return depth_scaled_;
}

double Modulator::get_depth_scale_low()
{
    return depth_low_;
}

double Modulator::get_depth_scale_high()
{
    return depth_high_;
}

double Modulator::get_depth_scale_exponent()
{
    return depth_exponent_;
}

Frame Modulator::process()
{
    Frame frame;

    if(muted_ || (freq_ == 0 && (freq_fixed_ == true)))
    {
        frame = 1;
        return frame; // good return value for am and fm
    }

    //set frequency of generator
    set_gen_freq();

    frame = gen_.operator ()();

    //check amods
    if(!amods_.empty())
    {
        Frame am_frame = visit_children(amods_);
        frame *= am_frame;
    }
    // if we are an fmod, amplify our signal by depth
    if(child_type_ == PARAMETER::FREQUENCY)
    {
        Frame depth_frame = get_depth_value();
        frame *= depth_frame;
    }

    return frame;
}

void Modulator::step()
{
    for (unsigned int i = 0; i < amods_.size(); i++) {
        SynthItem *item = amods_[i];
        item->step();
    }
    for (unsigned int i = 0; i < fmods_.size(); i++) {
        SynthItem *item = fmods_[i];
        item->step();
    }
}

void Modulator::block_start()
{
    if(!command_buffer_.empty())
    {
        retrieve_commands();
    }
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
    case COMMAND::SCALE_LOW:
        process_set_param_scale_low(command.doubles[0], command.parameter);
        break;
    case COMMAND::SCALE_HIGH:
        process_set_param_scale_high(command.doubles[0], command.parameter);
        break;
    case COMMAND::SCALE_EXPONENT:
        process_set_param_scale_exponent(command.doubles[0], command.parameter);
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
        child->add_parent(this);
        break;
    case PARAMETER::FREQUENCY:
        insert_item_unique(child, &fmods_);
        child->add_parent(this);
        break;
    default:
        break; //incompatible child type
    }
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
    child_type_ = parameter;
    std::vector<SynthItem*> parents_copy = parents_;
    for(unsigned int i = 0; i < parents_copy.size(); i++)
    {
        SynthItem* parent = parents_copy[i];
        erase_item(parent, &parents_);
        parent->remove_child(this);
        parent->add_child(this, child_type_);
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

void Modulator::process_set_param_scale_low(double low, SynthItem::PARAMETER param)
{
    if(param == PARAMETER::FREQUENCY)
    {
        freq_low_ = low;
    }
}

void Modulator::process_set_param_scale_high(double high, SynthItem::PARAMETER param)
{
    if(param == PARAMETER::FREQUENCY)
    {
        freq_high_ = high;
    }
}

void Modulator::process_set_param_scale_exponent(double exponent, SynthItem::PARAMETER param)
{
    if(param == PARAMETER::FREQUENCY)
    {
        freq_exponent_ = exponent;
    }
}

void Modulator::set_gen_freq()
{
    Frame fm_frame = 0;
    if(fmods_.size() > 0) {
        fm_frame = visit_children(fmods_);
    }

    if (freq_fixed_ == true || freq_indexes_.size() < 1) //no data mappings, use fixed freq
    {
        gen_.freq(freq_ + fm_frame.left);
    }
    else
    { // map each indexed value from the data row to the freq of a generator
        int idx = freq_indexes_[0];
        double freq = data_->at(idx);
        if(freq_scaled_)
        {
            freq = scale(freq, mins_->at(freq_indexes_[0]), maxes_->at(freq_indexes_[0]), freq_low_, freq_high_, freq_exponent_);
        }
        gen_.freq(freq + fm_frame.left);
    }
}

float Modulator::get_depth_value()
{
    float depth_value = 0;
    if (depth_fixed_ == true || depth_indexes_.size() < 1) // no data mappings, use fixed depth_
    {
        depth_value = depth_;
    }
    else
    {
        int idx = depth_indexes_[0];
        depth_value = data_->at(idx);
        if(depth_scaled_)
        {
            depth_value = scale(depth_value, mins_->at(depth_indexes_[0]), maxes_->at(depth_indexes_[0]), depth_low_, depth_high_, depth_exponent_);
        }
    }
    return depth_value;
}

}
