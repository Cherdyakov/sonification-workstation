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

void Envelope::set_attack_scale_vals(double low, double high, double exp)
{
    SynthItemCommand command;
    command.type = COMMAND::SCALE_VALS;
    command.parameter = PARAMETER::ATTACK;
    command.doubles.push_back(low);
    command.doubles.push_back(high);
    command.doubles.push_back(exp);
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

void Envelope::set_decay_scale_vals(double low, double high, double exp)
{
    SynthItemCommand command;
    command.type = COMMAND::SCALE_VALS;
    command.parameter = PARAMETER::DECAY;
    command.doubles.push_back(low);
    command.doubles.push_back(high);
    command.doubles.push_back(exp);
    command_buffer_.push(command);
}


Frame Envelope::process()
{
    Frame frame;

    if(!command_buffer_.empty())
    {
        retrieve_commands();
    }

    if(muted_)
    {
        return frame;
    }

    // retrigger if necessary
    if(env_.done()) {
        reset();
    }
    // get the envelope value
    frame = env_();

    // multiply by input
    if(!inputs_.empty())
    {
        Frame inFrame = visit_children(inputs_);
        inFrame /= inputs_.size();
        frame *= inFrame;
    }

    // modulate
    if(!amods_.empty())
    {
        Frame am_frame = visit_children(amods_);
        frame *= am_frame;
    }

    return frame;
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

void Envelope::process_set_param_scale_vals(double low, double high, double exp, SynthItem::PARAMETER param)
{
    if(param == PARAMETER::ATTACK)
    {
        attack_low_ = low;
        attack_high_ = high;
        attack_exponent_ = exp;
    }
    else if(param == PARAMETER::DECAY)
    {
        decay_low_ = low;
        decay_high_ = high;
        decay_exponent_ = exp;
    }
}

double Envelope::calculate_attack()
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

    return attack;
}

double Envelope::calculate_decay()
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

    return decay;
}

void Envelope::reset()
{
    env_.attack(calculate_attack());
    env_.decay(calculate_decay());
    env_.reset();
}

}
