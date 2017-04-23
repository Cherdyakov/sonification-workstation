#include "audifier.h"

namespace son {

Audifier::Audifier()
{
    myType = ITEM_TYPE::AUDIFIER;
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
            // Audifier always scales datasets to range -1.0 to 1.0
            sample += scale((dataItem->at(static_cast<unsigned int>(dataIndexes[i]))),
                            mins->at(i), maxes->at(i),
                            -1.0, 1.0);
        }
    }

    // visit amods eventually goes here

    // divide by total number of datasets mapped (rows)
    // to prevent clipping
    return sample /  dataIndexes.size();
}

float Audifier::process(float in)
{
    return in;
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
    command.parameter = ITEM_PARAMETER::AUDIFICATION;
    command.ints = indexes;
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
        if(command.parameter == ITEM_PARAMETER::AUDIFICATION)
        {
            processSetIndexes(command.ints);
        }
        break;
    }
    default:
        SynthItem::processCommand(command);
        break;
    }
}

void Audifier::processAddChild(SynthItem *child, SynthItem::ITEM_CHILD_TYPE type)
{
    switch (type){
    case ITEM_CHILD_TYPE::AMOD: {
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
