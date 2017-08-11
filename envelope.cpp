#include "envelope.h"
#include "utility.h"

namespace son {

Envelope::Envelope()
{
    my_type_ = ITEM::ENVELOPE;
    muted_ = false;
    attack_ = 0.01;
    attack_fixed_ = true;
    attack_scaled_ = true;
    attack_high_ = 0.9;
    attack_low_ = 0.1;
    attack_exponent_ = 1;
    decay_ = 0.1;
    decay_fixed_ = true;
    decay_scaled_ = true;
    decay_low_ = 0.1;
    decay_high_ = 1.0;
    decay_exponent_ = 1;

    current_segment_ = SEGMENT::ATTACK;
    position_in_segment_ = 0;
    num_attack_frames_ = 1;
    num_decay_length_ = 1;
    last_value_ = 0;
    start_value_ = 0;
    attack_delta_ = 0;
    done_ = true;

    accepted_children_ = {
        PARAMETER::AMPLITUDE,
        PARAMETER::INPUT
    };

}

Envelope::~Envelope()
{

}

void Envelope::delete_item()
{
    SynthItemCommand command;
    command.type = COMMAND::DELETE;
    command_buffer_.push(command);
}

SynthItem::ITEM Envelope::get_type()
{
    return my_type_;
}

void Envelope::set_data(std::vector<double> *data, std::vector<double> *mins, std::vector<double> *maxes)
{
    SynthItemCommand command;
    command.type = COMMAND::DATA;
    command.data = data;
    command.mins = mins;
    command.maxes = maxes;
    command_buffer_.push(command);
}

void Envelope::add_parent(SynthItem *parent)
{
    SynthItemCommand command;
    command.type = COMMAND::ADD_PARENT;
    command.item = parent;
    command_buffer_.push(command);
}

void Envelope::remove_parent(SynthItem *parent)
{
    SynthItemCommand command;
    command.type = COMMAND::REMOVE_PARENT;
    command.item = parent;
    command_buffer_.push(command);
}

bool Envelope::add_child(SynthItem *child, SynthItem::PARAMETER param)
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

void Envelope::remove_child(SynthItem *child)
{
    SynthItemCommand command;
    command.type = COMMAND::REMOVE_CHILD;
    command.item = child;
    command_buffer_.push(command);
}

void Envelope::mute(bool mute)
{
    SynthItemCommand command;
    command.type = COMMAND::MUTE;
    command.bool_val = mute;
    command_buffer_.push(command);
}

void Envelope::set_attack(double att)
{
    SynthItemCommand command;
    command.type = COMMAND::PARAM;
    command.parameter = PARAMETER::ATTACK;
    command.doubles.push_back(att);
    command_buffer_.push(command);
}

void Envelope::set_attack_fixed(bool fixed)
{
    SynthItemCommand command;
    command.type = COMMAND::FIXED;
    command.parameter = PARAMETER::ATTACK;
    command.bool_val = fixed;
    command_buffer_.push(command);
}

void Envelope::set_attack_indexes(std::vector<int> indexes)
{
    SynthItemCommand command;
    command.type = COMMAND::INDEXES;
    command.parameter = PARAMETER::ATTACK;
    command.ints.assign(indexes.begin(), indexes.end());
    command_buffer_.push(command);
}

void Envelope::set_attack_scaled(bool scaled)
{
    SynthItemCommand command;
    command.type = COMMAND::SCALED;
    command.parameter = PARAMETER::ATTACK;
    command.bool_val = scaled;
    command_buffer_.push(command);
}

void Envelope::set_attack_scale_low(double low)
{
    SynthItemCommand command;
    command.type = COMMAND::SCALE_LOW;
    command.parameter = PARAMETER::ATTACK;
    command.doubles.push_back(low);
    command_buffer_.push(command);
}

void Envelope::set_attack_scale_high(double high)
{
    SynthItemCommand command;
    command.type = COMMAND::SCALE_HIGH;
    command.parameter = PARAMETER::ATTACK;
    command.doubles.push_back(high);
    command_buffer_.push(command);
}

void Envelope::set_attack_scale_exponent(double exponent)
{
    SynthItemCommand command;
    command.type = COMMAND::SCALE_EXPONENT;
    command.parameter = PARAMETER::ATTACK;
    command.doubles.push_back(exponent);
    command_buffer_.push(command);
}

void Envelope::set_decay(double dur)
{
    SynthItemCommand command;
    command.type = COMMAND::PARAM;
    command.parameter = PARAMETER::DECAY;
    command.doubles.push_back(dur);
    command_buffer_.push(command);
}

void Envelope::set_decay_fixed(bool fixed)
{
    SynthItemCommand command;
    command.type = COMMAND::FIXED;
    command.parameter = PARAMETER::DECAY;
    command.bool_val = fixed;
    command_buffer_.push(command);
}

void Envelope::set_decay_indexes(std::vector<int> indexes)
{
    SynthItemCommand command;
    command.type = COMMAND::INDEXES;
    command.parameter = PARAMETER::DECAY;
    command.ints.assign(indexes.begin(), indexes.end());
    command_buffer_.push(command);
}

void Envelope::set_decay_scaled(bool scaled)
{
    SynthItemCommand command;
    command.type = COMMAND::SCALED;
    command.parameter = PARAMETER::DECAY;
    command.bool_val = scaled;
    command_buffer_.push(command);
}

void Envelope::set_decay_scale_low(double low)
{
    SynthItemCommand command;
    command.type = COMMAND::SCALE_LOW;
    command.parameter = PARAMETER::DECAY;
    command.doubles.push_back(low);
    command_buffer_.push(command);
}

void Envelope::set_decay_scale_high(double high)
{
    SynthItemCommand command;
    command.type = COMMAND::SCALE_HIGH;
    command.parameter = PARAMETER::DECAY;
    command.doubles.push_back(high);
    command_buffer_.push(command);
}

void Envelope::set_decay_scale_exponent(double exponent)
{
    SynthItemCommand command;
    command.type = COMMAND::SCALE_EXPONENT;
    command.parameter = PARAMETER::DECAY;
    command.doubles.push_back(exponent);
    command_buffer_.push(command);
}

bool Envelope::get_mute()
{
    return muted_;
}

std::vector<SynthItem *> Envelope::get_parents()
{
    return parents_;
}

double Envelope::get_attack()
{
    return attack_;
}

bool Envelope::get_attack_fixed()
{
    return attack_fixed_;
}

std::vector<int> Envelope::get_attack_indexes()
{
    return attack_indexes_;
}

bool Envelope::get_attack_scaled()
{
    return attack_scaled_;
}

double Envelope::get_attack_scale_low()
{
    return attack_low_;
}

double Envelope::get_attack_scale_high()
{
    return attack_high_;
}

double Envelope::get_attack_scale_exponent()
{
    return attack_exponent_;
}

double Envelope::get_decay()
{
    return decay_;
}

bool Envelope::get_decay_fixed()
{
    return decay_fixed_;
}

std::vector<int> Envelope::get_decay_indexes()
{
    return decay_indexes_;
}

bool Envelope::get_decay_scaled()
{
    return decay_scaled_;
}

double Envelope::get_decay_scale_low()
{
    return decay_low_;
}

double Envelope::get_decay_scale_high()
{
    return decay_high_;
}

double Envelope::get_decay_scale_exponent()
{
    return decay_exponent_;
}

Frame Envelope::process()
{
    float value;
    Frame frame;

    if(!command_buffer_.empty())
    {
        retrieve_commands();
    }

    if(muted_ || done_)
    {
        return frame;
    }

    // no need to generate output if no input
    if(!inputs_.empty())
    {
        // get input
        Frame in_frame = visit_children(inputs_);
        in_frame /= inputs_.size();
        // generate envelope value and apply to output frame
        value = calculate_envelope_value();
        frame = in_frame * value;
    }

    // modulate
    if(!amods_.empty())
    {
        Frame am_frame = visit_children(amods_);
        frame *= am_frame;
    }

    // move envelope position before next call
    advance_position();

    // value to begin from on reset()
    last_value_ = value;

    return frame;
}

void Envelope::step()
{
    for (unsigned int i = 0; i < amods_.size(); i++) {
        SynthItem *item = amods_[i];
        item->step();
    }
    for (unsigned int i = 0; i < inputs_.size(); i++) {
        SynthItem *item = inputs_[i];
        item->step();
    }
    reset();
}

void Envelope::retrieve_commands()
{
    while(command_buffer_.pop(&current_command_))
    {
        process_command(current_command_);
    }
}

void Envelope::process_command(SynthItem::SynthItemCommand command)
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

void Envelope::process_add_child(SynthItem *child, SynthItem::PARAMETER parameter)
{
    switch (parameter){
    case PARAMETER::AMPLITUDE:
        insert_item_unique(child, &amods_);
        child->add_parent(this);
        break;
    case PARAMETER::INPUT:
        insert_item_unique(child, &inputs_);
        child->add_parent(this);
        break;
    default:
        break; //incompatible child type
    }
}

void Envelope::process_remove_child(SynthItem *child)
{
    erase_item(child, &inputs_);
    erase_item(child, &amods_);
}

void Envelope::process_delete_item()
{
    remove_as_child(this, parents_);
    remove_as_parent(this, inputs_);
    remove_as_parent(this, amods_);
    delete this;
}

void Envelope::process_set_data(std::vector<double> *data, std::vector<double> *mins, std::vector<double> *maxes)
{
    data_ = data;
    mins_ = mins;
    maxes_ = maxes;
}

void Envelope::process_set_param_value(double val, SynthItem::PARAMETER param)
{
    if(param == PARAMETER::ATTACK)
    {
        attack_ = val;
    }
    else if(param == PARAMETER::DECAY)
    {
        decay_ = val;
    }
}

void Envelope::process_set_param_fixed(bool fixed, SynthItem::PARAMETER param)
{
    if(param == PARAMETER::ATTACK)
    {
        attack_fixed_ = fixed;
    }
    else if(param == PARAMETER::DECAY)
    {
        decay_fixed_ = fixed;
    }
}

void Envelope::process_set_param_indexes(std::vector<int> indexes, SynthItem::PARAMETER param)
{
    if(param == PARAMETER::ATTACK)
    {
        attack_indexes_ = indexes;
    }
    else if(param == PARAMETER::DECAY)
    {
        decay_indexes_ = indexes;
    }
}

void Envelope::process_set_param_scaled(bool scaled, SynthItem::PARAMETER param)
{
    if(param == PARAMETER::ATTACK)
    {
        attack_scaled_ = scaled;
    }
    else if(param == PARAMETER::DECAY)
    {
        decay_scaled_ = scaled;
    }
}

void Envelope::process_set_param_scale_low(double low, SynthItem::PARAMETER param)
{
    if(param == PARAMETER::ATTACK)
    {
        attack_low_ = low;
    }
    else if(param == PARAMETER::DECAY)
    {
        decay_low_ = low;
    }
}

void Envelope::process_set_param_scale_high(double high, SynthItem::PARAMETER param)
{
    if(param == PARAMETER::ATTACK)
    {
        attack_high_ = high;
    }
    else if(param == PARAMETER::DECAY)
    {
        decay_high_ = high;
    }
}

void Envelope::process_set_param_scale_exponent(double exponent, SynthItem::PARAMETER param)
{
    if(param == PARAMETER::ATTACK)
    {
        attack_exponent_ = exponent;
    }
    else if(param == PARAMETER::DECAY)
    {
        decay_exponent_ = exponent;
    }
}

unsigned int Envelope::calculate_num_attack_frames()
{
    double attack;

    if(attack_fixed_ || attack_indexes_.size() < 1)
    {
        attack = attack_;
    }
    else
    {
        int idx = attack_indexes_[0];
        attack = data_->at(idx);
        if(attack_scaled_)
        {
            attack = scale(attack, mins_->at(idx), maxes_->at(idx), attack_low_, attack_high_, attack_exponent_);
        }
    }

    double num_frames = attack * FRAME_RATE;
    return (unsigned int)num_frames;
}

unsigned int Envelope::calculate_num_decay_frames()
{
    double decay;

    if(decay_fixed_ || decay_indexes_.size() < 1)
    {
        decay = decay_;
    }
    else
    {
        int idx = decay_indexes_[0];
        decay = data_->at(idx);
        if(decay_scaled_)
        {
            decay = scale(decay, mins_->at(idx), maxes_->at(idx), decay_low_, decay_high_, decay_exponent_);
        }
    }

    double num_frames = decay * FRAME_RATE;
    return (unsigned int)num_frames;
}

float Envelope::calculate_envelope_value()
{
    float value = 0;
    // calculate envelope value
    switch(current_segment_)
    {
    case SEGMENT::ATTACK:
        value = start_value_ + ((position_in_segment_ / (float)num_attack_frames_) * attack_delta_);
        break;
    case SEGMENT::DECAY:
        value = 1.0 - (position_in_segment_ / (float)num_decay_length_);
        break;
    default:
        break;
    }
    return value;
}

void Envelope::advance_position()
{
    position_in_segment_++;
    if(current_segment_ == SEGMENT::ATTACK)
    {
        if(position_in_segment_ > num_attack_frames_)
        {
            current_segment_ = SEGMENT::DECAY;
            position_in_segment_ = 0;
        }
    }
    if(current_segment_ == SEGMENT::DECAY)
    {
        if(position_in_segment_ > num_decay_length_)
        {
            done_ = true;
        }
    }
}

void Envelope::reset()
{
    num_attack_frames_ = calculate_num_attack_frames();
    num_decay_length_ = calculate_num_decay_frames();

    // to prevent discontinuity attack starts
    // from last_value_ and goes to 1, rather
    // than resetting to 0 every time
    start_value_ = last_value_;
    attack_delta_ = 1 - start_value_;

    current_segment_ = SEGMENT::ATTACK;
    position_in_segment_ = 0;

    done_ = false;
}

} // son

