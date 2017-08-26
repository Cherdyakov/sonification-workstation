#include "panner.h"
#include "math.h"
#include "utility.h"

namespace  son {

Panner::Panner()
{
    my_type_ = ITEM::PANNER;
    muted_ = false;
    pan_ = 0;
    pan_fixed_ = true;
    pan_scaled_ = true;
    pan_low_ = -1;
    pan_high_ = 1;
    pan_exponent_ = 1;

    accepted_children_ = {
        PARAMETER::INPUT,
        PARAMETER::AMPLITUDE
    };
}

void Panner::delete_item()
{
    SynthItemCommand command;
    command.type = COMMAND::DELETE;
    command_buffer_.push(command);
}

SynthItem::ITEM Panner::get_type()
{
    return my_type_;
}

void Panner::set_data(std::vector<double> *data, std::vector<double> *mins, std::vector<double> *maxes)
{
    SynthItemCommand command;
    command.type = COMMAND::DATA;
    command.data = data;
    command.mins = mins;
    command.maxes = maxes;
    command_buffer_.push(command);
}

void Panner::add_parent(SynthItem *parent)
{
    SynthItemCommand command;
    command.type = COMMAND::ADD_PARENT;
    command.item = parent;
    command_buffer_.push(command);
}

void Panner::remove_parent(SynthItem *parent)
{
    SynthItemCommand command;
    command.type = COMMAND::REMOVE_PARENT;
    command.item = parent;
    command_buffer_.push(command);
}

bool Panner::add_child(SynthItem *child, SynthItem::PARAMETER param)
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

void Panner::remove_child(SynthItem *child)
{
    SynthItemCommand command;
    command.type = COMMAND::REMOVE_CHILD;
    command.item = child;
    command_buffer_.push(command);
}

void Panner::mute(bool mute)
{
    SynthItemCommand command;
    command.type = COMMAND::MUTE;
    command.bool_val = mute;
    command_buffer_.push(command);
}

void Panner::set_pan(double pan)
{
    SynthItemCommand command;
    command.type = COMMAND::PARAM;
    command.parameter = PARAMETER::PAN;
    command.doubles.push_back(pan);
    command_buffer_.push(command);
}

void Panner::set_pan_fixed(bool fixed)
{
    SynthItemCommand command;
    command.type = COMMAND::FIXED;
    command.parameter = PARAMETER::PAN;
    command.bool_val = fixed;
    command_buffer_.push(command);
}

void Panner::set_pan_indexes(std::vector<int> indexes)
{
    SynthItemCommand command;
    command.type = COMMAND::INDEXES;
    command.parameter = PARAMETER::PAN;
    command.ints.assign(indexes.begin(), indexes.end());
    command_buffer_.push(command);
}

void Panner::set_pan_scaled(bool scaled)
{
    SynthItemCommand command;
    command.type = COMMAND::SCALED;
    command.parameter = PARAMETER::PAN;
    command.bool_val = scaled;
    command_buffer_.push(command);
}

void Panner::set_pan_scale_low(double low)
{
    SynthItemCommand command;
    command.type = COMMAND::SCALE_LOW;
    command.parameter = PARAMETER::PAN;
    command.doubles.push_back(low);
    command_buffer_.push(command);
}

void Panner::set_pan_scale_high(double high)
{
    SynthItemCommand command;
    command.type = COMMAND::SCALE_HIGH;
    command.parameter = PARAMETER::PAN;
    command.doubles.push_back(high);
    command_buffer_.push(command);
}

void Panner::set_pan_scale_exponent(double exponent)
{
    SynthItemCommand command;
    command.type = COMMAND::SCALE_EXPONENT;
    command.parameter = PARAMETER::PAN;
    command.doubles.push_back(exponent);
    command_buffer_.push(command);
}

bool Panner::get_mute()
{
    return muted_;
}

std::vector<SynthItem *> Panner::get_parents()
{
    return parents_;
}

double Panner::get_pan()
{
    return pan_;
}

bool Panner::get_pan_fixed()
{
    return pan_fixed_;
}

std::vector<int> Panner::get_pan_indexes()
{
    return pan_indexes_;
}

bool Panner::get_pan_scaled()
{
    return pan_scaled_;
}

double Panner::get_pan_scale_low()
{
    return pan_low_;
}

double Panner::get_pan_scale_high()
{
    return pan_high_;
}

double Panner::get_pan_scale_exponent()
{
    return pan_exponent_;
}

// Generate a frame of output
Frame Panner::process()
{
    Frame frame;

    if(!command_buffer_.empty())
    {
        retrieve_commands();
    }

    if(muted_ || inputs_.size() < 1)
    {
        return frame;
    }

    // generate frame from all inputs
    for (unsigned int i = 0; i < inputs_.size(); ++i) {
        frame += inputs_[i]->process();
    }
    frame /= inputs_.size();

    // calculate the pan pos between -1 and 1
    float pan_pos = calculate_pan_pos();

    // pan the frame using linear taper, we are
    // dealing mostly with correlated signals
    pan_pos = (pan_pos + 1) / 2;
    frame.left *= (1.0 - pan_pos);
    frame.right *= pan_pos;

    // visit amplitude modulating children
    if(!amods_.empty())
    {
        Frame am_frame = visit_children(amods_);
        frame *= am_frame;
    }

    return frame;
}

void Panner::step()
{
    for (unsigned int i = 0; i < amods_.size(); i++) {
        SynthItem *item = amods_[i];
        item->step();
    }
    for (unsigned int i = 0; i < inputs_.size(); i++) {
        SynthItem *item = inputs_[i];
        item->step();
    }
}

void Panner::retrieve_commands()
{
    while(command_buffer_.pop(&current_command_))
    {
        process_command(current_command_);
    }
}

void Panner::process_command(SynthItem::SynthItemCommand command)
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

void Panner::process_add_child(SynthItem *child, SynthItem::PARAMETER parameter)
{
    switch (parameter){
    case PARAMETER::INPUT:
        insert_item_unique(child, &inputs_);
        child->add_parent(this);
        break;
    case PARAMETER::AMPLITUDE:
        insert_item_unique(child, &amods_);
        child->add_parent(this);
        break;
    default:
        break; //incompatible child type
    }
}

void Panner::process_remove_child(SynthItem *child)
{
    erase_item(child, &inputs_);
    erase_item(child, &amods_);
}

void Panner::process_delete_item()
{
    remove_as_child(this, parents_);
    remove_as_parent(this, inputs_);
    remove_as_parent(this, amods_);
    delete this;
}

void Panner::process_set_data(std::vector<double> *data, std::vector<double> *mins, std::vector<double> *maxes)
{
    data_ = data;
    mins_ = mins;
    maxes_ = maxes;
}

void Panner::process_set_param_value(double val, SynthItem::PARAMETER param)
{
    if(param == PARAMETER::PAN)
    {
        pan_ = val;
    }
}

void Panner::process_set_param_fixed(bool fixed, SynthItem::PARAMETER param)
{
    if(param == PARAMETER::PAN)
    {
        pan_fixed_ = fixed;
    }
}

void Panner::process_set_param_indexes(std::vector<int> indexes, SynthItem::PARAMETER param)
{
    if(param == PARAMETER::PAN)
    {
        pan_indexes_ = indexes;
    }
}

void Panner::process_set_param_scaled(bool scaled, SynthItem::PARAMETER param)
{
    if(param == PARAMETER::PAN)
    {
        pan_scaled_ = scaled;
    }
}

void Panner::process_set_param_scale_low(double low, SynthItem::PARAMETER param)
{
    if(param == PARAMETER::PAN)
    {
        pan_low_ = low;
    }
}

void Panner::process_set_param_scale_high(double high, SynthItem::PARAMETER param)
{
    if(param == PARAMETER::PAN)
    {
        pan_high_ = high;
    }
}

void Panner::process_set_param_scale_exponent(double exponent, SynthItem::PARAMETER param)
{
    if(param == PARAMETER::PAN)
    {
        pan_exponent_ = exponent;
    }
}

double Panner::calculate_pan_pos()
{
    double pan_pos = 0;
    if(pan_fixed_ || pan_indexes_.size() < 1) {
        pan_pos = pan_;
    }
    else {
        int idx = pan_indexes_[0];
        pan_pos = data_->at(idx);
        pan_pos = scale(pan_pos, mins_->at(idx), maxes_->at(idx), pan_low_, pan_high_, pan_exponent_);
    }
    return pan_pos;
}



} // namespace son
