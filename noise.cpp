#include "noise.h"

namespace son {

Noise::Noise()
{
    my_type_ = ITEM::NOISE;
    muted_ = false;
    noise_type_ = NOISE::WHITE;

    accepted_children_ = {
        PARAMETER::AMPLITUDE
    };
}

void Noise::delete_self()
{
    SynthItemCommand command;
    command.type = COMMAND::DELETE;
    command_buffer_.push(command);
}

SynthItem::ITEM Noise::get_type()
{
    return my_type_;
}

void Noise::set_data(std::vector<double> *data, std::vector<double> *mins, std::vector<double> *maxes)
{
    SynthItemCommand command;
    command.type = COMMAND::DATA;
    command.data = data;
    command.mins = mins;
    command.maxes = maxes;
    command_buffer_.push(command);
}

void Noise::add_parent(SynthItem *parent)
{
    SynthItemCommand command;
    command.type = COMMAND::ADD_PARENT;
    command.item = parent;
    command_buffer_.push(command);
}

void Noise::remove_parent(SynthItem *parent)
{
    SynthItemCommand command;
    command.type = COMMAND::REMOVE_PARENT;
    command.item = parent;
    command_buffer_.push(command);
}

bool Noise::add_child(SynthItem *child, SynthItem::PARAMETER param)
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

void Noise::remove_child(SynthItem *child)
{
    SynthItemCommand command;
    command.type = COMMAND::REMOVE_CHILD;
    command.item = child;
    command_buffer_.push(command);
}

void Noise::mute(bool mute)
{
    SynthItemCommand command;
    command.type = COMMAND::MUTE;
    command.bool_val = mute;
    command_buffer_.push(command);
}

void Noise::set_noise(NOISE noise)
{
    SynthItemCommand command;
    command.type = COMMAND::NOISE;
    command.ints.push_back((int)noise);
    command_buffer_.push(command);
}

bool Noise::get_mute()
{
    return muted_;
}

std::vector<SynthItem *> Noise::get_parents()
{
    return parents_;
}

SynthItem::NOISE Noise::get_noise()
{
    return noise_type_;
}

// Generate a frame of output
Frame Noise::process()
{
    Frame frame;

    if(muted_)
    {
        return frame;
    }

    switch (noise_type_) {
    case NOISE::WHITE:
        frame = white_();
        break;
    case NOISE::PINK:
        frame = pink_();
    default:
        break;
    }

    // visit amplitude modulating children
    if(!amods_.empty())
    {
        Frame am_frame = visit_children(amods_);
        frame *= am_frame;
    }

    return frame;
}

void Noise::step()
{
    for (unsigned int i = 0; i < amods_.size(); i++) {
        SynthItem *item = amods_[i];
        item->step();
    }
}

void Noise::control_process()
{
    if(!command_buffer_.empty())
    {
        retrieve_commands();
    }
}

void Noise::retrieve_commands()
{
    while(command_buffer_.pop(&current_command_))
    {
        process_command(current_command_);
    }
}

void Noise::process_command(SynthItem::SynthItemCommand command)
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
        remove_item(command.item, &parents_);
        break;
    case COMMAND::MUTE:
        muted_ = command.bool_val;
        break;
    case COMMAND::NOISE:
        process_set_noise((NOISE)command.ints[0]);
        break;
    case COMMAND::DELETE:
        process_delete();
        break;
    default:
        break;
    }
}

void Noise::process_add_child(SynthItem *child, SynthItem::PARAMETER parameter)
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

void Noise::process_remove_child(SynthItem *child)
{
    remove_item(child, &inputs_);
    remove_item(child, &amods_);
}

void Noise::process_delete()
{
    remove_as_child(this, parents_);
    remove_as_parent(this, inputs_);
    remove_as_parent(this, amods_);
    delete this;
}

void Noise::process_set_data(std::vector<double> *data, std::vector<double> *mins, std::vector<double> *maxes)
{
    data_ = data;
    mins_ = mins;
    maxes_ = maxes;
}

void Noise::process_set_noise(NOISE noise)
{
    noise_type_ = noise;
}

} // namespace son
