#include "modulator.h"

namespace son {

Modulator::Modulator()
{

}

void Modulator::setModType(SynthItem::CHILD_TYPE modType)
{
    SynthItemCommand command;
    command.type = ITEM_COMMAND_TYPE::MOD_TYPE;
    command.childType = modType;
    commandBuffer.push(command);
}

void Modulator::processCommand(SynthItem::SynthItemCommand command)
{
    ITEM_COMMAND_TYPE type = command.type;

    switch (type) {
    case ITEM_COMMAND_TYPE::MOD_TYPE:
    {
        processSetModType(command.childType);
        break;
    }
    default:
        Oscillator::processCommand(command);
        break;
    }
}

void Modulator::processSetModType(SynthItem::CHILD_TYPE modType)
{

}

}
