#include "audifier.h"

namespace son {

Audifier::Audifier()
{
    my_type_ = ITEM::AUDIFIER;

    accepted_children_ = {
        PARAMETER::AMPLITUDE
    };
}

Audifier::~Audifier()
{

}

void Audifier::delete_item()
{

}

SynthItem::ITEM Audifier::get_type()
{
    return my_type_;
}

void Audifier::set_data(std::vector<double> *data, std::vector<double> mins, std::vector<double> maxes)
{

}

void Audifier::add_parent(SynthItem *parent)
{

}

void Audifier::remove_parent(SynthItem *parent)
{

}

bool Audifier::add_child(SynthItem *child, SynthItem::PARAMETER param)
{

}

void Audifier::remove_child(SynthItem *item)
{

}

void Audifier::mute(bool mute)
{

}

float Audifier::process()
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
    for(unsigned int i = 0; i < audify_indexes_.size(); i++)
    {
        // Audifier always scales datasets to range -1.0 to 1.0
        sample += scale((data_->at(static_cast<unsigned int>(audify_indexes_[i]))),
                        mins_.at(i), maxes_.at(i),
                        -1.0, 1.0, 1.0);
    }

    // vist amplitude modulating children
    if(!amods_.empty())
    {
        float am_sample = visit_children(amods_);
        sample *= am_sample;
    }

    // divide by total number of datasets mapped (rows)
    // to prevent clipping
    return sample /  audify_indexes_.size();
}

void Audifier::retrieve_commands()
{

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
        insert_item_unique(command.item, parents_);
        break;
    case COMMAND::REMOVE_PARENT:
        erase_item(command.item, parents_);
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
        insert_item_unique(child, amods_);
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

void Audifier::process_set_data(std::vector<double> *data, std::vector<double> mins, std::vector<double> maxes)
{

}

void Audifier::process_set_param_indexes(std::vector<int> indexes, PARAMETER param)
{
    if(param == PARAMETER::AUDIFICATION)
    {

        audify_indexes_ = indexes;
    }
}


} // namespace son
