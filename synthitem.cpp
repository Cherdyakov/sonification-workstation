#include "synthitem.h"
#include "Gamma.h"

namespace son {

SynthItem::ITEM SynthItem::getType()
{
    return myType;
}

SynthItem::SynthItem()
{
    muted = false;
    data = NULL;
    mins = NULL;
    maxes = NULL;
}

void SynthItem::removeParent(SynthItem *parent)
{
    SynthItemCommand command;
    command.type = COMMAND::REMOVE_PARENT;
    command.item = parent;
    commandBuffer.push(command);
}

bool SynthItem::addChild(SynthItem *child, PARAMETER parameter)
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

void SynthItem::deleteItem()
{
    SynthItemCommand command;
    command.type = COMMAND::DELETE;
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
    COMMAND type = command.type;

    switch (type) {

    case COMMAND::DATA:
        processSetData(command.data, command.mins, command.maxes);
        break;
    case COMMAND::ADD_CHILD:
        processAddChild(command.item, command.parameter);
        break;
    case COMMAND::REMOVE_CHILD:
        processRemoveChild(command.item);
        break;
    case COMMAND::ADD_PARENT:
        processAddParent(command.item);
        break;
    case COMMAND::REMOVE_PARENT:
        processRemoveParent(command.item);
        break;
    case COMMAND::MUTE:
        processMute(command.boolVal);
        break;
    case COMMAND::DELETE:
        processDeleteItem();
        break;
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
    if(std::find(parents.begin(), parents.end(), parent) != parents.end()) {
        return;
    } else {
        parents.push_back(parent);
    }
}

void SynthItem::processSetData(std::vector<double> *dataItem,
                                   std::vector<double> *mins,
                                   std::vector<double> *maxes)
{
    this->data = dataItem;
    this->mins = mins;
    this->maxes = maxes;
}

bool SynthItem::verifyChildParameter(PARAMETER childParameter)
{
    bool accept = (std::find(acceptedChildren.begin(), acceptedChildren.end(), childParameter) == acceptedChildren.end());
    return accept;
}

float SynthItem::visitChildren(std::vector<SynthItem*> children)
{
    float s = 0.0;
    for (unsigned int i = 0; i < children.size(); ++i)
    {
        SynthItem* gen = children[i];
        s += gen->process();
    }
    s /= children.size();
    return s;
}

void SynthItem::addParent(SynthItem *parent)
{
    SynthItemCommand command;
    command.type = COMMAND::ADD_PARENT;
    command.item = parent;
    commandBuffer.push(command);
}

void SynthItem::removeChild(SynthItem *item)
{
    SynthItemCommand command;
    command.type = COMMAND::REMOVE_CHILD;
    command.item = item;
    commandBuffer.push(command);
}

void SynthItem::setData(std::vector<double> *data,
                        std::vector<double>* mins,
                        std::vector<double>* maxes)
{
    SynthItemCommand command;
    command.type = COMMAND::DATA;
    command.data = data;
    command.mins = mins;
    command.maxes = maxes;
    commandBuffer.push(command);
}

void SynthItem::setIndexes(std::vector<int> indexes, SynthItem::PARAMETER parameter)
{
    SynthItemCommand command;
    command.type = COMMAND::INDEXES;
    command.parameter = parameter;
    for (unsigned int i = 0; i < indexes.size(); i++) {
        command.ints.push_back(indexes[i]);
    }
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
