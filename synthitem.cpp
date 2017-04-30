#include "synthitem.h"
#include "Gamma.h"

namespace son {

SynthItem::ITEM SynthItem::getType()
{

}

SynthItem::SynthItem()
{
    muted = false;
    data = NULL;
    mins = NULL;
    maxes = NULL;
}

void SynthItem::remove_parent(SynthItem *parent)
{
    SynthItemCommand command;
    command.type = COMMAND::REMOVE_PARENT;
    command.item = parent;
    commandBuffer.push(command);
}

bool SynthItem::add_child(SynthItem *child, PARAMETER parameter)
{
    if(!verifyChildParameter(parameter))
    {
        return false;
    }
    SynthItemCommand command;
    command.type = COMMAND::ADD_CHILD;
    command.item = child;
    command.parameter = parameter;
    commandBuffer.push(command);
    return true;
}

void SynthItem::mute(bool mute)
{
    SynthItemCommand command;
    command.type = COMMAND::MUTE;
    command.boolVal = mute;
    commandBuffer.push(command);
}

void SynthItem::delete_item()
{
    SynthItemCommand command;
    command.type = COMMAND::DELETE;
    commandBuffer.push(command);
}

void SynthItem::retrieve_commands()
{
    while(commandBuffer.pop(&currentCommand))
    {
        process_command(currentCommand);
    }
}

void SynthItem::process_command(SynthItemCommand command)
{
    COMMAND type = command.type;

    switch (type) {

    case COMMAND::DATA:
        process_set_data(command.data_, command.mins_, command.maxes);
        break;
    case COMMAND::ADD_CHILD:
        process_add_child(command.item, command.parameter);
        break;
    case COMMAND::REMOVE_CHILD:
        process_remove_child(command.item);
        break;
    case COMMAND::ADD_PARENT:
        process_add_parent(command.item);
        break;
    case COMMAND::REMOVE_PARENT:
        process_remove_parent(command.item);
        break;
    case COMMAND::MUTE:
        process_mute(command.boolVal);
        break;
    case COMMAND::DELETE:
        process_delete_item();
        break;
    default:
        break;
    }
}

void SynthItem::process_mute(bool mute)
{
    muted = mute;
}

void SynthItem::process_remove_parent(SynthItem *parent)
{
    if(parent)
    {
        parents.erase(std::remove(parents.begin(), parents.end(), parent), parents.end());
    }
}

void SynthItem::process_add_parent(SynthItem *parent)
{
    if(std::find(parents.begin(), parents.end(), parent) != parents.end()) {
        return;
    } else {
        parents.push_back(parent);
    }
}

void SynthItem::process_set_data(std::vector<double> *dataItem,
                                   std::vector<double> *mins,
                                   std::vector<double> *maxes)
{
    this->data = dataItem;
    this->mins = mins;
    this->maxes = maxes;
}





void SynthItem::add_parent(SynthItem *parent)
{
    SynthItemCommand command;
    command.type = COMMAND::ADD_PARENT;
    command.item = parent;
    commandBuffer.push(command);
}

void SynthItem::remove_child(SynthItem *item)
{
    SynthItemCommand command;
    command.type = COMMAND::REMOVE_CHILD;
    command.item = item;
    commandBuffer.push(command);
}

void SynthItem::set_data(std::vector<double> *data,
                        std::vector<double> mins,
                        std::vector<double> maxes)
{
    SynthItemCommand command;
    command.type = COMMAND::DATA;
    command.data_ = data;
    command.mins_ = mins;
    command.maxes = maxes;
    commandBuffer.push(command);
}

void SynthItem::set_indexes(std::vector<int> indexes, SynthItem::PARAMETER parameter)
{
    SynthItemCommand command;
    command.type = COMMAND::INDEXES;
    command.parameter = parameter;
    for (unsigned int i = 0; i < indexes.size(); i++) {
        command.ints.push_back(indexes[i]);
    }
    commandBuffer.push(command);
}



} //namespace son
