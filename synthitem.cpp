#include "synthitem.h"
#include "Gamma.h"

namespace son {

SynthItem::ITEM_TYPE SynthItem::getType()
{
    return myType;
}

SynthItem::ITEM_CHILD_TYPE SynthItem::getChildType()
{
    return myChildType;
}

SynthItem::SynthItem()
{
    muted = false;
    dataItem = NULL;
    mins = NULL;
    maxes = NULL;
}

void SynthItem::removeParent(SynthItem *parent)
{
    SynthItemCommand command;
    command.type = ITEM_COMMAND_TYPE::REMOVE_PARENT;
    command.item = parent;
    commandBuffer.push(command);
}

bool SynthItem::addChild(SynthItem *child)
{
    if(!verifyChildType(child->getChildType()))
    {
        return false;
    }
    SynthItemCommand command;
    command.type = ITEM_COMMAND_TYPE::ADD_CHILD;
    command.item = child;
    command.childType = child->getChildType();
    commandBuffer.push(command);
    return true;
}

void SynthItem::mute(bool mute)
{
    SynthItemCommand command;
    command.type = ITEM_COMMAND_TYPE::MUTE;
    command.boolVal = mute;
    commandBuffer.push(command);
}

void SynthItem::destroy()
{
    SynthItemCommand command;
    command.type = ITEM_COMMAND_TYPE::DESTROY;
    commandBuffer.push(command);
}

void SynthItem::retrieveCommands()
{
    while(commandBuffer.pop(&currentCommand))
    {
        processCommand(currentCommand);
    }
}

void SynthItem::processCommand(SynthItemCommand command)
{
    ITEM_COMMAND_TYPE type = command.type;

    switch (type) {

    case ITEM_COMMAND_TYPE::DATA:
    {
        processSetDataItem(command.data, command.mins, command.maxes);
        break;
    }
    case ITEM_COMMAND_TYPE::ADD_PARENT:
    {
        processAddParent(command.item);
        break;
    }
    case ITEM_COMMAND_TYPE::REMOVE_PARENT:
    {
        processRemoveParent(command.item);
        break;
    }
    case ITEM_COMMAND_TYPE::MUTE:
    {
        processMute(command.boolVal);
        break;
    }
    case ITEM_COMMAND_TYPE::DESTROY:
    {
        processDestroy();
        break;
    }
    default:
        break;
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

void SynthItem::processSetDataItem(std::vector<double> *dataItem,
                                   std::vector<double> *mins,
                                   std::vector<double> *maxes)
{
    this->dataItem = dataItem;
    this->mins = mins;
    this->maxes = maxes;
}

bool SynthItem::verifyChildType(SynthItem::ITEM_CHILD_TYPE childType)
{
    if(std::find(acceptedChildTypes.begin(), acceptedChildTypes.end(), childType) == acceptedChildTypes.end())
    {
        return false;
    }
    return true;
}

float SynthItem::visitAmods()
{
    float s = 0.0;
    for (unsigned int i = 0; i < amods.size(); ++i)
    {
        SynthItem* gen = amods[i];
        s += gen->process();
    }
    s /= amods.size();
    return s;
}

void SynthItem::addParent(SynthItem *parent)
{
    SynthItemCommand command;
    command.type = ITEM_COMMAND_TYPE::ADD_PARENT;
    command.item = parent;
    commandBuffer.push(command);
}

void SynthItem::removeChild(SynthItem *item)
{
    SynthItemCommand command;
    command.type = ITEM_COMMAND_TYPE::REMOVE_CHILD;
    command.item = item;
    commandBuffer.push(command);
}

void SynthItem::setDataItem(std::vector<double> *data,
                            std::vector<double>* mins,
                            std::vector<double>* maxes)
{
    SynthItemCommand command;
    command.type = ITEM_COMMAND_TYPE::DATA;
    command.data = data;
    command.mins = mins;
    command.maxes = maxes;
    commandBuffer.push(command);
}

// based on the Max "Scale" object
// https://docs.cycling74.com/max7/maxobject/scale
// default exp = 1 is linear
double SynthItem::scale(double x, double in_low, double in_high,
                        double out_low, double out_high, double exp)
{
    return ((x-in_low)/(in_high-in_low) == 0) ? out_low : (((x-in_low)/(in_high-in_low)) > 0) ? (out_low + (out_high-out_low) * pow(((x-in_low)/(in_high-in_low)),exp)) : ( out_low + (out_high-out_low) * -(pow((((-x+in_low)/(in_high-in_low))),exp)));
}

} //namespace son
