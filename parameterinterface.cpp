#include "parameterinterface.h"
#include <QDebug>

namespace sow {

ParameterInterface::ParameterInterface(QObject *parent) : QObject(parent)
{
    // Interface variables, bound to QML.
    setValue(440.0f);
    setFixed(true);
    setScaled(true);
    setScaleOutLow(100.0f);
    setScaleOutHigh(8000.0f);
    setScaleExp(1);
    setMap("");
}

void ParameterInterface::connectInterface(Parameter* parameter)
{
    parameter_ = parameter;

    // Connect this interface to a backing Parameter.
    connect(this, &ParameterInterface::iParameterChanged,
            parameter, &Parameter::onParameterChanged);

    // Signal the backing Parameter with the initial values.
    iParameterChanged(ENUMS::SUB_PARAMETER::VALUE, iValue_);
    iParameterChanged(ENUMS::SUB_PARAMETER::FIXED, iFixed_);
    iParameterChanged(ENUMS::SUB_PARAMETER::SCALED, iScale_);
    iParameterChanged(ENUMS::SUB_PARAMETER::SCALE_OUT_LOW, iScaleOutLow_);
    iParameterChanged(ENUMS::SUB_PARAMETER::SCALE_OUT_HIGH, iScaleOutHigh_);
    iParameterChanged(ENUMS::SUB_PARAMETER::SCALE_EXP, iScaleExp_);
    iParameterChanged(ENUMS::SUB_PARAMETER::SCALE_IN_LOW, iScaleInLow_);
    iParameterChanged(ENUMS::SUB_PARAMETER::SCALE_IN_HIGH, iScaleInHigh_);
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

void sow::ParameterInterface::setValue(const float value) {
    if (!qFuzzyCompare(iValue_, value)) {
        iValue_ =  value;
        emit valueChanged();
        iParameterChanged(ENUMS::SUB_PARAMETER::VALUE, iValue_);
    }
}

float sow::ParameterInterface::value() const {
    return iValue_;
}

void sow::ParameterInterface::setFixed(const bool fixed) {
    if (iFixed_ != fixed) {
        iFixed_ =  fixed;
        emit fixedChanged();
        iParameterChanged(ENUMS::SUB_PARAMETER::FIXED, iFixed_);
    }
}

bool sow::ParameterInterface::fixed() const {
    return iFixed_;
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

void ParameterInterface::setScaleInLow(const float scaleInLow)
{
    if (!qFuzzyCompare(iScaleInLow_, scaleInLow)) {
        iScaleInLow_ =  scaleInLow;
        iParameterChanged(ENUMS::SUB_PARAMETER::SCALE_IN_LOW, iScaleInLow_);
    }
}

float ParameterInterface::scaleInLow()
{
    return iScaleInLow_;
}

void ParameterInterface::setScaleInHigh(const float scaleInHigh)
{
    if (!qFuzzyCompare(iScaleInHigh_, scaleInHigh)) {
        iScaleInHigh_ =  scaleInHigh;
        iParameterChanged(ENUMS::SUB_PARAMETER::SCALE_IN_HIGH, iScaleInHigh_);
    }
}

float ParameterInterface::scaleInHigh()
{
    return iScaleInHigh_;
}

bool sow::ParameterInterface::setMap(const QString map) {
    if (iMap_ != map) {
        iMap_ = map;
        return parameter_->setMap(iMap_);
    }
    return true;
}

QString sow::ParameterInterface::map() const {
    return iMap_;
}

} // Namespace sow.
