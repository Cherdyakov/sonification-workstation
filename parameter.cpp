#include "parameter.h"
#include <QString>
#include <QDebug>

namespace sow {

Parameter::Parameter(QObject *parent) : QObject(parent)
{

}

// Connect an interface to this Parameter
void Parameter::connectInterface(ParameterInterface *interface)
{
    connect(interface, &ParameterInterface::iParameterChanged,
            this, &Parameter::onParameterChanged);
    connect(interface, &ParameterInterface::iMapChanged,
            this, &Parameter::onMapChanged);
}

// Process outstanding ParameterCommands
void Parameter::controlProcess()
{
    while(commandBuffer_.pop(&currentCommand_)) {
        processCommand(currentCommand_);
    }
}

// Execute commands pulled from the command buffer
void Parameter::processCommand(sow::ParameterCommand cmd)
{
    ENUMS::SUB_PARAMETER subParam = cmd.subParam;

    switch (subParam) {
    case ENUMS::SUB_PARAMETER::VALUE:
        value_ = cmd.value;
        break;
    case ENUMS::SUB_PARAMETER::FIXED:
        fixed_ = (cmd.value != 0.0f);
        break;
    case ENUMS::SUB_PARAMETER::SCALED:
        scaled_ = (cmd.value != 0.0f);
        break;
    case ENUMS::SUB_PARAMETER::SCALE_LO:
        scaleLo_ = cmd.value;
        break;
    case ENUMS::SUB_PARAMETER::SCALE_HI:
        scaleHi_ = cmd.value;
        break;
    case ENUMS::SUB_PARAMETER::SCALE_EXP:
        scaleExp_ = cmd.value;
        break;
    case ENUMS::SUB_PARAMETER::MAP:
        map_ = QString(cmd.map);
        break;
    }

    qDebug() << "processCommand: " + QString::number((int)subParam) + " " + QString::number(cmd.value) + " " + map_;
}

// Slot for updated float values from the interface
void Parameter::onParameterChanged(const ENUMS::SUB_PARAMETER subParam, const float value)
{
    ParameterCommand cmd;
    cmd.subParam = subParam;
    cmd.value = value;
    commandBuffer_.push(cmd);
    qDebug() << "onParameterChanged: " + QString::number((int)subParam) + " " + QString::number(cmd.value);

}

// Slot for updated parameter mapping from the interface
void Parameter::onMapChanged(const QString map)
{
    ParameterCommand cmd;
    cmd.subParam = ENUMS::SUB_PARAMETER::MAP;
    // QString to QChar array to pass through command buffer
    const QChar* unicode = map.unicode();
    for(int i = 0; i < map.length(); i++) {
        cmd.map[i] = unicode[i];
    }

    commandBuffer_.push(cmd);
    qDebug() << "onMapChanged: " + map;

}

} // namespace sow
