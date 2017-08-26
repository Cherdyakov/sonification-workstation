#include "audifier.h"

namespace son {

Audifier::Audifier()
{
    my_type_ = ITEM::AUDIFIER;
    muted_ = false;

    accepted_children_ = {
        PARAMETER::AMPLITUDE
    };
}

Audifier::~Audifier()
{

}

void Audifier::delete_item()
{
    SynthItemCommand command;
    command.type = COMMAND::DELETE;
    command_buffer_.push(command);
}

SynthItem::ITEM Audifier::get_type()
{
    return my_type_;
}

void Audifier::set_data(std::vector<double> *data, std::vector<double>* mins, std::vector<double>* maxes)
{
    SynthItemCommand command;
    command.type = COMMAND::DATA;
    command.data = data;
    command.mins = mins;
    command.maxes = maxes;
    command_buffer_.push(command);
}

void Audifier::add_parent(SynthItem *parent)
{
    SynthItemCommand command;
    command.type = COMMAND::ADD_PARENT;
    command.item = parent;
    command_buffer_.push(command);
}

void Audifier::remove_parent(SynthItem *parent)
{
    SynthItemCommand command;
    command.type = COMMAND::REMOVE_PARENT;
    command.item = parent;
    command_buffer_.push(command);
}

bool Audifier::add_child(SynthItem *child, PARAMETER param)
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

void Audifier::remove_child(SynthItem *child)
{
    SynthItemCommand command;
    command.type = COMMAND::REMOVE_CHILD;
    command.item = child;
    command_buffer_.push(command);
}

void Audifier::mute(bool mute)
{
    SynthItemCommand command;
    command.type = COMMAND::MUTE;
    command.bool_val = mute;
    command_buffer_.push(command);
}

void Audifier::set_aud_indexes(std::vector<int> indexes)
{
    SynthItemCommand command;
    command.type = COMMAND::INDEXES;
    command.parameter = PARAMETER::AUDIFICATION;
    command.ints = indexes;
    command_buffer_.push(command);
}

bool Audifier::get_mute()
{
    return muted_;
}

std::vector<SynthItem *> Audifier::get_parents()
{
    return parents_;
}

std::vector<int> Audifier::get_aud_indexes()
{
    return audify_indexes_;
}

Frame Audifier::process()
{
    Frame frame = 0.0;

    if(muted_)
    {
        return frame;
    }
    else if(audify_indexes_.size() < 1)
    {
        return frame;
    }

    for(unsigned int i = 0; i < audify_indexes_.size(); i++)
    {
        // Audifier always scales datasets to range -1.0 to 1.0
        frame += scale((data_->at(static_cast<unsigned int>(audify_indexes_[i]))),
                       mins_->at(i), maxes_->at(i),
                       -1.0, 1.0, 1.0);
    }

    // visit amplitude modulating children
    if(!amods_.empty())
    {
        Frame am_frame = visit_children(amods_);
        frame *= am_frame;
    }

    // divide by total number of datasets mapped (rows)
    // to prevent clipping
    return frame /  audify_indexes_.size();
}

void Audifier::step()
{
    for (unsigned int i = 0; i < amods_.size(); i++) {
        SynthItem *item = amods_[i];
        item->step();
    }
}

void Audifier::block_start()
{
    if(!command_buffer_.empty())
    {
        retrieve_commands();
    }
    for (unsigned int i = 0; i < amods_.size(); ++i)
    {
        SynthItem* item = amods_[i];
        item->block_start();
    }
}

void Audifier::retrieve_commands()
{
    while(command_buffer_.pop(&current_command_))
    {
        process_command(current_command_);
    }
}

void Audifier::process_command(SynthItemCommand command)
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
    case COMMAND::INDEXES:
        process_set_param_indexes(command.ints, command.parameter);
        break;
    case COMMAND::DELETE:
        process_delete_item();
        break;
    default:
        break;
    }
}

void Audifier::process_add_child(SynthItem *child, PARAMETER param)
{
    if(param == PARAMETER::AMPLITUDE)
    {
        insert_item_unique(child, &amods_);
        child->add_parent(this);
    }
}

void Audifier::process_remove_child(SynthItem *child)
{
    amods_.erase(std::remove(amods_.begin(), amods_.end(), child), amods_.end());
}

void Audifier::process_delete_item()
{
    remove_as_child(this, parents_);
    remove_as_parent(this, amods_);
    delete this;
}

void Audifier::process_set_data(std::vector<double> *data, std::vector<double>* mins, std::vector<double>* maxes)
{
    data_ = data;
    mins_ = mins;
    maxes_ = maxes;
}

void Audifier::process_set_param_indexes(std::vector<int> indexes, PARAMETER param)
{
    if(param == PARAMETER::AUDIFICATION)
    {
        audify_indexes_ = indexes;
    }
}


} // namespace son
