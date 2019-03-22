#include "parameter.h"
#include <QString>
#include <QDebug>

namespace sow {

Parameter::Parameter(QObject *parent) : QObject(parent)
{

}

float Parameter::value()
{
    return evaluator_.value();
}

// Process outstanding ParameterCommands
void Parameter::controlProcess()
{
    ParameterCommand currentCommand_;
    while(commandBuffer_.pop(&currentCommand_)) {
        processCommand(currentCommand_);
    }
    DatasetCommand currentDatasetCommand_;
    while(datasetCommandBuffer_.pop(&currentDatasetCommand_)) {
        processDatasetCommand(currentDatasetCommand_);
    }
}

bool Parameter::setMap(const QString map)
{
    if(!evaluator_.testCompileExpression(map.toStdString(), data_)) {
        return false;
    }

    ParameterCommand cmd;
    cmd.subParam = ENUMS::SUB_PARAMETER::MAP;
    // QString to QChar array to pass through command buffer
    const QChar* unicode = map.unicode();
    for(int i = 0; i < map.length(); i++) {
        cmd.map[i] = unicode[i];
    }
    commandBuffer_.push(cmd);

    return true;
}

void Parameter::setData(std::vector<float>* const data, std::vector<float>* const mins, std::vector<float>* const maxes)
{
    DatasetCommand cmd;
    cmd.data = data;
    cmd.mins = mins;
    cmd.maxes = maxes;
    datasetCommandBuffer_.push(cmd);
}

// Execute commands pulled from the command buffer
void Parameter::processCommand(sow::ParameterCommand cmd)
{
    ENUMS::SUB_PARAMETER subParam = cmd.subParam;

    switch (subParam) {
    case ENUMS::SUB_PARAMETER::SCALED:
        scale_ = (cmd.value != 0.0f);
        break;
    case ENUMS::SUB_PARAMETER::SCALE_OUT_LOW:
        scaler_.setOutLow(cmd.value);
        break;
    case ENUMS::SUB_PARAMETER::SCALE_OUT_HIGH:
        scaler_.setOutHigh(cmd.value);
        break;
    case ENUMS::SUB_PARAMETER::SCALE_EXP:
        scaler_.setExp(cmd.value);
        break;
    case ENUMS::SUB_PARAMETER::SCALE_IN_LOW:
        scaler_.setInLow(cmd.value);
        break;
    case ENUMS::SUB_PARAMETER::SCALE_IN_HIGH:
        scaler_.setInHigh(cmd.value);
        break;
    case ENUMS::SUB_PARAMETER::MAP:
        map_ = QString(cmd.map);
        processSetMap(map_.toStdString());
        break;
    }
}

void Parameter::processDatasetCommand(DatasetCommand cmd)
{
    data_ = cmd.data;
    mins_ = cmd.mins;
    maxes_ = cmd.maxes;
}

void Parameter::processSetMap(std::string expression)
{
    evaluator_.compileExpression(expression);
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
