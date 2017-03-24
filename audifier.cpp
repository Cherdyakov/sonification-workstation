#include "audifier.h"

namespace son {

Audifier::Audifier()
{

}

float Audifier::process()
{
    float sample = 0.0;

    if(!commandBuffer.empty())
    {
        retrieveCommands();
    }
    if(muted)
    {
        return sample;
    }
    if(dataItem)
    {
        for(unsigned int i = 0; i < dataIndexes.size(); i++)
        {
            sample += (dataItem->at(dataIndexes[i]) / 1000000000.0);
        }
    }

    //visit amods eventually goes here
    return sample /  dataIndexes.size();
}

float Audifier::process(float in)
{
    return in;
}

void Audifier::addChild(SynthItem *child, CHILD_TYPE type)
{
    SynthItemCommand command;
    command.type = ITEM_COMMAND_TYPE::ADD_CHILD;
    command.item = child;
    commandBuffer.push(command);
}

void Audifier::removeChild(SynthItem *child)
{
    SynthItemCommand command;
    command.type = ITEM_COMMAND_TYPE::REMOVE_CHILD;
    command.item = child;
    commandBuffer.push(command);
}

void Audifier::setIndexes(std::vector<int> indexes)
{
    SynthItemCommand command;
    command.type = ITEM_COMMAND_TYPE::INDEXES;
    command.indexes = indexes;
    commandBuffer.push(command);
}

void Audifier::processCommand(SynthItemCommand command)
{
    ITEM_COMMAND_TYPE type = command.type;

    switch (type) {
    case ITEM_COMMAND_TYPE::ADD_CHILD:
    {
        processAddChild(command.item, command.childType);
        break;
    }
    case ITEM_COMMAND_TYPE::REMOVE_CHILD:
    {
        processRemoveChild(command.item);
        break;
    }
    case ITEM_COMMAND_TYPE::INDEXES:
    {
        processSetIndexes(command.indexes);
        break;
    }
    default:
        SynthItem::processCommand(command);
        break;
    }
}

void Audifier::processAddChild(SynthItem *child, SynthItem::CHILD_TYPE type)
{
    switch (type){
    case CHILD_TYPE::AMOD: {
        if(std::find(amods.begin(), amods.end(), child) != amods.end()) {
            return;
        } else {
            amods.push_back(child);
        }
        break;
    }
    default:
        break; //incompatible child type
    }
}

void Audifier::processRemoveChild(SynthItem *child)
{
    amods.erase(std::remove(amods.begin(), amods.end(), child), amods.end());
}

void Audifier::processSetIndexes(std::vector<int> indexes)
{
    bool m = muted;
    if(!muted) {
        muted = true;
    }
    dataIndexes = indexes;

    muted = m;
}

float Audifier::visitAmods()
{
    float s = 0.0;
    for (unsigned int i = 0; i < amods.size(); ++i)
    {
        SynthItem* gen = amods[i];
        s += gen->process();
    }
    return s;
}

}
