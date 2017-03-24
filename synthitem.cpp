#include "synthitem.h"
#include "Gamma.h"

namespace son {

SynthItem::SynthItem()
{
    muted = false;
    dataItem = NULL;
}

void SynthItem::removeParent(SynthItem *parent)
{
    SynthItemCommand command;
    command.type = ITEM_COMMAND_TYPE::REMOVE_PARENT;
    command.item = parent;
    commandBuffer.push(command);
}

void SynthItem::mute(bool mute)
{
    SynthItemCommand command;
    command.type = ITEM_COMMAND_TYPE::MUTE;
    command.mute = mute;
    commandBuffer.push(command);
}

void SynthItem::retrieveCommands()
{
    while(commandBuffer.pop(&currentCommand))
    {
        processCommand(currentCommand);
    }
}

void SynthItem::processMute(bool mute)
{
    muted = mute;
}

void SynthItem::processRemoveParent(SynthItem *parent)
{
    if(parent)
    {
        parents.erase(std::remove(parents.begin(), parents.end(), parent), parents.end());
    }
}

void SynthItem::processAddParent(SynthItem *parent)
{
    if(parent)
    {
        if(std::find(parents.begin(), parents.end(), parent) != parents.end()) {
            return;
        } else {
            parents.push_back(parent);
        }
    }
}

void SynthItem::addParent(SynthItem *parent)
{
    SynthItemCommand command;
    command.type = ITEM_COMMAND_TYPE::ADD_PARENT;
    command.item = parent;
    commandBuffer.push(command);
}

void SynthItem::setDataItem(std::vector<double> *data)
{
    dataItem = data;
}

} //namespace son
