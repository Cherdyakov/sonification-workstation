#include "synthitem.h"

namespace son {

SynthItem::SynthItem()
{
    muted = false;
    dataItem = NULL;
    myType = ITEM_TYPE::NONE;
}

SynthItem::ITEM_TYPE SynthItem::type()
{
    return myType;
}

void SynthItem::mute(bool mute)
{
    SynthItemCommand command;
    command.type = SYNTH_ITEM_COMMAND_TYPE::MUTE;
    command.boolData = mute;
    commandBuffer.push(command);
}

void SynthItem::setParameterIndexes(std::vector<int> indexes, std::__cxx11::string param)
{
    SynthItemCommand command;
    command.type = SYNTH_ITEM_COMMAND_TYPE::PARAM_INDEXES;
    command.intVec = indexes;
    command.paramName = param;
    commandBuffer.push(command);
}

void SynthItem::setParameterValues(std::vector<double> values, std::__cxx11::string param)
{
    SynthItemCommand command;
    command.type = SYNTH_ITEM_COMMAND_TYPE::PARAM_VALUES;
    command.paramValues = values;
    command.paramName = param;
    commandBuffer.push(command);
}

void SynthItem::removeChild(SynthItem *child)
{
    SynthItemCommand command;
    command.type = SYNTH_ITEM_COMMAND_TYPE::REMOVE_CHILD;
    command.child = child;
    commandBuffer.push(command);
}

void SynthItem::addChild(SynthItem *child, CHILD_TYPE type)
{
    SynthItemCommand command;
    command.type = SYNTH_ITEM_COMMAND_TYPE::ADD_CHILD;
    command.child = child;
    command.childType = type;
    commandBuffer.push(command);
}

void SynthItem::setDataItem(std::vector<double> *data)
{
    SynthItemCommand command;
    command.type = SYNTH_ITEM_COMMAND_TYPE::DATA;
    command.data = data;
    commandBuffer.push(command);
}

float SynthItem::process(float in)
{
    return in;
}

float SynthItem::process()
{
    return 0;
}

void SynthItem::retrieveCommands()
{
    while(commandBuffer.pop(&currentCommand))
    {
        parseCommand(currentCommand);
    }
}

void SynthItem::parseCommand(SynthItemCommand command)
{
    SYNTH_ITEM_COMMAND_TYPE type = command.type;

    switch (type) {
    case SYNTH_ITEM_COMMAND_TYPE::DATA:
    {
        processSetDataItem((std::vector<double>*)command.ptr);
        break;
    }
    case SYNTH_ITEM_COMMAND_TYPE::ADD_CHILD:
    {
        processAddChild((SynthItem*)command.ptr, (CHILD_TYPE)command.intsData[0]);
        break;
    }
    case SYNTH_ITEM_COMMAND_TYPE::REMOVE_CHILD:
    {
        processRemoveChild((SynthItem*)command.ptr);
        break;
    }
    case SYNTH_ITEM_COMMAND_TYPE::MUTE:
    {
        processMute(command.boolData);
        break;
    }
    case SYNTH_ITEM_COMMAND_TYPE::DELETE:
    {
        break;
    }
    default:
        break;
    }
}

void SynthItem::processSetDataItem(std::vector<double> *data)
{
    dataItem = data;
}

void SynthItem::processAddChild(SynthItem *child, CHILD_TYPE type)
{
    if(std::find(children.begin(), children.end(), child) != children.end()) {
        return;
    } else {
        children.push_back(child);
        (void)type;
    }
}

void SynthItem::processRemoveChild(SynthItem *child)
{
    children.erase(std::remove(children.begin(), children.end(), child), children.end());
}

void SynthItem::processSetParameterIndexes(std::vector<int> indexes, std::__cxx11::string param)
{
    (void)indexes;
    (void)param;
}

void SynthItem::processSetParameterValues(std::vector<double> values, std::__cxx11::string param)
{
    (void)values;
    (void)param;
}

void SynthItem::processSetParameterFixed(bool fixed, std::__cxx11::string param)
{
    (void)fixed;
    (void)param;
}

void SynthItem::processMute(bool mute)
{
    muted = mute;
}

} //namespace son
