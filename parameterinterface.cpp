#include "parameterinterface.h"
#include <QDebug>

namespace sow {

ParameterInterface::ParameterInterface(QObject *parent) : QObject(parent)
{
    // Interface variables, bound to QML
    iValue_ = 440.0f;
    iFixed_ = true;
    iScaled_ = true;
    iScaleLo_ = 100.0f;
    iScaleHi_ = 8000.0f;
    iScaleExp_ = 1.0f;
    iMap_ = QString();
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

void sow::ParameterInterface::setScaled(const bool scaled) {
    if (iScaled_ != scaled) {
        iScaled_ =  scaled;
        emit scaledChanged();
        iParameterChanged(ENUMS::SUB_PARAMETER::SCALED, iScaled_);
    }
}

bool sow::ParameterInterface::scaled() const {
    return iScaled_;
}

void sow::ParameterInterface::setScaleLo(const float scaleLo) {
    if (!qFuzzyCompare(iScaleLo_, scaleLo)) {
        iScaleLo_ =  scaleLo;
        emit scaleLoChanged();
        iParameterChanged(ENUMS::SUB_PARAMETER::SCALE_LO, iScaleLo_);
    }
}

float sow::ParameterInterface::scaleLo() const {
    return iScaleLo_;
}

void sow::ParameterInterface::setScaleHi(const float scaleHi) {
    if (!qFuzzyCompare(iScaleHi_, scaleHi)) {
        iScaleHi_ =  scaleHi;
        emit scaleHiChanged();
        iParameterChanged(ENUMS::SUB_PARAMETER::SCALE_HI, iScaleHi_);
    }
}

float sow::ParameterInterface::scaleHi() const {
    return iScaleHi_;
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

void sow::ParameterInterface::setMap(const QString map) {
    if (iMap_ != map) {
        iMap_ = map;
        emit nameChanged();
        iMapChanged(iMap_);
    }
}

QString sow::ParameterInterface::map() const {
    return iMap_;
}

} // Namespace sow.
