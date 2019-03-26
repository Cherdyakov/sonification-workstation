#include "parameterfloat.h"
#include <QString>
#include <QDebug>

namespace sow {

ParameterFloat::ParameterFloat(QObject *parent) : QObject(parent)
{

}

float ParameterFloat::value()
{
    float val;
    if(scale_) {
        val = mapEvaluator_.scaledValue(scaleOutLow_, scaleOutHigh_, scaleExponent_);
    } else {
        val = mapEvaluator_.value();

    }
    return val;
}

// Process outstanding ParameterCommands
void ParameterFloat::controlProcess()
{
    ParameterCommand currentCommand_;
    while(commandBuffer_.pop(&currentCommand_)) {
        processCommand(currentCommand_);
    }
}

bool ParameterFloat::setMap(const QString map)
{
    if(!mapEvaluator_.testCompileExpression(map.toStdString())) {
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

void ParameterFloat::setData(const Dataset *dataset, const std::vector<float> *currentData)
{
    mapEvaluator_.setData(dataset, currentData);
}

// Execute commands pulled from the command buffer
void ParameterFloat::processCommand(sow::ParameterCommand cmd)
{
    ENUMS::SUB_PARAMETER subParam = cmd.subParam;

    switch (subParam) {
    case ENUMS::SUB_PARAMETER::SCALED:
        scale_ = (cmd.value != 0.0f);
        break;
    case ENUMS::SUB_PARAMETER::SCALE_EXP:
        scaleExponent_ = cmd.value;
        break;
    case ENUMS::SUB_PARAMETER::SCALE_OUT_LOW:
        scaleOutLow_ = cmd.value;
        break;
    case ENUMS::SUB_PARAMETER::SCALE_OUT_HIGH:
        scaleOutHigh_ = cmd.value;
        break;
    case ENUMS::SUB_PARAMETER::MAP:
        map_ = QString(cmd.map);
        processSetMap(map_.toStdString());
        break;
    }
}

void ParameterFloat::processSetMap(std::string expression)
{
    mapEvaluator_.compileExpression(expression);
}

// Slot for updated float values from the interface
void ParameterFloat::onParameterChanged(const ENUMS::SUB_PARAMETER subParam, const float value)
{
    ParameterCommand cmd;
    cmd.subParam = subParam;
    cmd.value = value;
    commandBuffer_.push(cmd);
}

} // namespace sow
