#include "modulator.h"

namespace son {

Modulator::Modulator()
{

}

void Modulator::setModType(SynthItem::ITEM_CHILD_TYPE childType)
{
    SynthItemCommand command;
    command.type = ITEM_COMMAND_TYPE::VALUE;
    command.parameter = ITEM_PARAMETER::MODULATION;
    command.childType = childType;
    commandBuffer.push(command);
}

void Modulator::processCommand(SynthItem::SynthItemCommand command)
{
    ITEM_COMMAND_TYPE type = command.type;

    switch (type) {
    case ITEM_COMMAND_TYPE::VALUE:
    {
        if(command.parameter == ITEM_PARAMETER::MODULATION)
        {
            processSetModType(command.childType);
        }
        break;
    }
    default:
        Oscillator::processCommand(command);
        break;
    }
}

void Modulator::processSetModType(SynthItem::ITEM_CHILD_TYPE modType)
{

}

}
