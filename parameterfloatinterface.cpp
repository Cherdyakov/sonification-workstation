#include "parameterfloatinterface.h"
#include <QDebug>

namespace sow {

ParameterFloatInterface::ParameterFloatInterface(QObject *parent) : QObject(parent)
{
    // Interface variables, bound to QML.
    setScaled(false);
    setScaleOutLow(100.0f);
    setScaleOutHigh(8000.0f);
    setScaleExp(1);
    setMap("440.0");
}

void ParameterFloatInterface::connectInterface(ParameterFloat* parameter)
{
    parameter_ = parameter;

    // Connect this interface to a backing Parameter.
    connect(this, &ParameterFloatInterface::iParameterChanged,
            parameter, &ParameterFloat::onParameterChanged);

    // Signal the backing Parameter with the initial values.
    iParameterChanged(ENUMS::SUB_PARAMETER::SCALED, iScale_);
    iParameterChanged(ENUMS::SUB_PARAMETER::SCALE_OUT_LOW, iScaleOutLow_);
    iParameterChanged(ENUMS::SUB_PARAMETER::SCALE_OUT_HIGH, iScaleOutHigh_);
    iParameterChanged(ENUMS::SUB_PARAMETER::SCALE_EXP, iScaleExp_);
    parameter_->setMap(iMap_);
}

void sow::ParameterFloatInterface::setType(const ENUMS::PARAMETER type) {
    if (iType_ != type) {
        iType_ = type;
        emit typeChanged();
    }
}
ENUMS::PARAMETER sow::ParameterFloatInterface::type() const {
    return iType_;
}

void sow::ParameterFloatInterface::setScaled(const bool scale) {
    if (iScale_ != scale) {
        iScale_ =  scale;
        emit scaledChanged();
        iParameterChanged(ENUMS::SUB_PARAMETER::SCALED, iScale_);
    }
}

bool sow::ParameterFloatInterface::scaled() const {
    return iScale_;
}

void sow::ParameterFloatInterface::setScaleOutLow(const float scaleOutLow) {
    if (!qFuzzyCompare(iScaleOutLow_, scaleOutLow)) {
        iScaleOutLow_ =  scaleOutLow;
        emit scaleLoChanged();
        iParameterChanged(ENUMS::SUB_PARAMETER::SCALE_OUT_LOW, iScaleOutLow_);
    }
}

float sow::ParameterFloatInterface::scaleOutLow() const {
    return iScaleOutLow_;
}

void sow::ParameterFloatInterface::setScaleOutHigh(const float scaleOutHigh) {
    if (!qFuzzyCompare(iScaleOutHigh_, scaleOutHigh)) {
        iScaleOutHigh_ =  scaleOutHigh;
        emit scaleHiChanged();
        iParameterChanged(ENUMS::SUB_PARAMETER::SCALE_OUT_HIGH, iScaleOutHigh_);
    }
}

float sow::ParameterFloatInterface::scaleOutHigh() const {
    return iScaleOutHigh_;
}

void sow::ParameterFloatInterface::setScaleExp(const float scaleExp) {
    if (!qFuzzyCompare(iScaleExp_, scaleExp)) {
        iScaleExp_ =  scaleExp;
        emit scaleExpChanged();
        iParameterChanged(ENUMS::SUB_PARAMETER::SCALE_EXP, iScaleExp_);
    }
}

float sow::ParameterFloatInterface::scaleExp() const {
    return iScaleExp_;
}

bool sow::ParameterFloatInterface::setMap(const QString map) {
    if (iMap_ != map) {
        iMap_ = map;
        emit mapChanged();
    }
    if(parameter_) {
        return parameter_->setMap(iMap_);
    }
    return false;
}

QString sow::ParameterFloatInterface::map() const {
    return iMap_;
}

} // Namespace sow.
