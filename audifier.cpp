#include "audifier.h"

namespace son {

Audifier::Audifier()
{

}

float Audifier::process()
{
    float s = 0.0;

    s = (dataItem->at(0) / 1000000000.0);

//    for(int i = 0; i < dataIndexes.count(); i++) {
////        qDebug() << dataColumn->at(dataIndexes[i]);
//        s = (dataColumn->at(dataIndexes[i]) / 32800.0) * 0.2;
//    }

    //visit amods eventually goes here
    return s;
}

float Audifier::process(float in)
{
    return in;
}

void Audifier::addChild(SynthItem *child, SON_CHILD_TYPE type)
{
    AudifierCommand command;
    command.type = SON_AUD_COMMAND_TYPE::ADD_CHILD;
    command.child = child;
    commandBuffer.push(command);
}

void Audifier::removeChild(SynthItem *child)
{
    AudifierCommand command;
    command.type = SON_AUD_COMMAND_TYPE::REMOVE_CHILD;
    command.child = child;
    commandBuffer.push(command);
}

void Audifier::setDataItem(std::vector<double> *data)
{
    AudifierCommand command;
    command.type = SON_AUD_COMMAND_TYPE::DATA;
    command.data = data;
    commandBuffer.push(command);
}

void Audifier::setIndexes(std::vector<int> indexes)
{
    AudifierCommand command;
    command.type = SON_AUD_COMMAND_TYPE::INDEXES;
    command.indexes = indexes;
    commandBuffer.push(command);
}

void Audifier::mute(bool mute)
{
    AudifierCommand command;
    command.type = SON_AUD_COMMAND_TYPE::MUTE;
    command.mute = mute;
    commandBuffer.push(command);
}

void Audifier::retrieveCommands()
{
    while(commandBuffer.pop(&currentCommand))
    {
        processCommand(currentCommand);
    }
}

void Audifier::processCommand(AudifierCommand command)
{
    SON_AUD_COMMAND_TYPE type = command.type;

    switch (type) {
    case SON_AUD_COMMAND_TYPE::ADD_CHILD:
    {
        processAddChild(command.child, command.childType);
        break;
    }
    case SON_AUD_COMMAND_TYPE::DATA:
    {
        processSetDataItem(command.data);
        break;
    }
    case SON_AUD_COMMAND_TYPE::INDEXES:
    {
        processSetIndexes(command.indexes);
        break;
    }
    case SON_AUD_COMMAND_TYPE::REMOVE_CHILD:
    {
        processRemoveChild(command.child);
        break;
    }
    case SON_AUD_COMMAND_TYPE::MUTE:
    {
        processMute(command.mute);
        break;
    }
    default:
        break;
    }
}

void Audifier::processAddChild(SynthItem *child, CHILD_TYPE type)
{
    switch (type){
    case SON_CHILD_TYPE::AMOD: {
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

void Audifier::processSetDataItem(std::vector<double> *data)
{
    dataItem = data;
    for(unsigned int i = 0; i < amods.size(); i++) {
        son::SynthItem* item = amods[i];
        item->setDataItem(data);
    }
}

void Audifier::processSetIndexes(std::vector<int> indexes)
{
    bool m = muted;
    if(!muted) {
        muted = true;
    }
    dataIndexes = indexes;

    resize(dataIndexes.size());

    muted = m;
}

void Audifier::processMute(bool mute)
{
    muted = mute;
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

void Audifier::resize(unsigned int size)
{
    // resize
}

}
