#include "parameter.h"

namespace sow {

Parameter::Parameter(QObject *parent) : QObject(parent)
{

}


// Process outstanding ParameterCommands
void Parameter::controlProcess()
{
    ParameterCommand currentCommand_;
    while(commandBuffer_.pop(&currentCommand_)) {
        processCommand(currentCommand_);
    }
}

void Parameter::setData(const Dataset *dataset, const std::vector<float> *currentData)
{
    Q_UNUSED(dataset)
    Q_UNUSED(currentData)
}

// Slot for updated float values from the interface
void Parameter::onParameterChanged(const ENUMS::SUB_PARAMETER subParam, const float value)
{
    ParameterCommand cmd;
    cmd.subParam = subParam;
    cmd.value = value;
    commandBuffer_.push(cmd);
}

} // namespace sow
