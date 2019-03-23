#include "parameterinterface.h"
#include <QDebug>

namespace sow {

ParameterInterface::ParameterInterface(QObject *parent) : QObject(parent)
{
    // Interface variables, bound to QML.
    setScaled(false);
    setScaleOutLow(100.0f);
    setScaleOutHigh(8000.0f);
    setScaleExp(1);
    setMap("440.0");
}

void ParameterInterface::connectInterface(Parameter* parameter)
{
    parameter_ = parameter;

    // Connect this interface to a backing Parameter.
    connect(this, &ParameterInterface::iParameterChanged,
            parameter, &Parameter::onParameterChanged);

    // Signal the backing Parameter with the initial values.
    iParameterChanged(ENUMS::SUB_PARAMETER::SCALED, iScale_);
    iParameterChanged(ENUMS::SUB_PARAMETER::SCALE_OUT_LOW, iScaleOutLow_);
    iParameterChanged(ENUMS::SUB_PARAMETER::SCALE_OUT_HIGH, iScaleOutHigh_);
    iParameterChanged(ENUMS::SUB_PARAMETER::SCALE_EXP, iScaleExp_);
    parameter_->setMap(iMap_);
}

void sow::ParameterInterface::setType(const ENUMS::PARAMETER type) {
    if (iType_ != type) {
        iType_ = type;
        emit typeChanged();
    }
}
ENUMS::PARAMETER sow::ParameterInterface::type() const {
    return iType_;
}

void sow::ParameterInterface::setScaled(const bool scale) {
    if (iScale_ != scale) {
        iScale_ =  scale;
        emit scaledChanged();
        iParameterChanged(ENUMS::SUB_PARAMETER::SCALED, iScale_);
    }
}

bool sow::ParameterInterface::scaled() const {
    return iScale_;
}

void sow::ParameterInterface::setScaleOutLow(const float scaleOutLow) {
    if (!qFuzzyCompare(iScaleOutLow_, scaleOutLow)) {
        iScaleOutLow_ =  scaleOutLow;
        emit scaleLoChanged();
        iParameterChanged(ENUMS::SUB_PARAMETER::SCALE_OUT_LOW, iScaleOutLow_);
    }
}

float sow::ParameterInterface::scaleOutLow() const {
    return iScaleOutLow_;
}

void sow::ParameterInterface::setScaleOutHigh(const float scaleOutHigh) {
    if (!qFuzzyCompare(iScaleOutHigh_, scaleOutHigh)) {
        iScaleOutHigh_ =  scaleOutHigh;
        emit scaleHiChanged();
        iParameterChanged(ENUMS::SUB_PARAMETER::SCALE_OUT_HIGH, iScaleOutHigh_);
    }
}

float sow::ParameterInterface::scaleOutHigh() const {
    return iScaleOutHigh_;
}

void sow::ParameterInterface::setScaleExp(const float scaleExp) {
    if (!qFuzzyCompare(iScaleExp_, scaleExp)) {
        iScaleExp_ =  scaleExp;
        emit scaleExpChanged();
        iParameterChanged(ENUMS::SUB_PARAMETER::SCALE_EXP, iScaleExp_);
    }
}

float sow::ParameterInterface::scaleExp() const {
    return iScaleExp_;
}

bool sow::ParameterInterface::setMap(const QString map) {
    if (iMap_ != map) {
        iMap_ = map;
        emit mapChanged();
    }
    if(parameter_) {
        return parameter_->setMap(iMap_);
    }
    return false;
}

QString sow::ParameterInterface::map() const {
    return iMap_;
}

} // Namespace sow.
