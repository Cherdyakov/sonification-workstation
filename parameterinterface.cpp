#include "parameterinterface.h"
#include <QDebug>

namespace sow {

ParameterInterface::ParameterInterface(QObject *parent) : QObject(parent)
{
    setFixed(true);
    setScaleLo(900);
}


void sow::ParameterInterface::setName(const QString name) {
    if (iName_ != name) {
        iName_ = name;
        emit nameChanged();
    }
    qDebug() << "setName: " + iName_;
}

QString sow::ParameterInterface::name() const {
    return iName_;
}

void sow::ParameterInterface::setType(const SowEnums::PARAMETER type) {
    if (iType_ != type) {
        iType_ = type;
        emit typeChanged();
    }
}
SowEnums::PARAMETER sow::ParameterInterface::type() const {
    return iType_;
}

void sow::ParameterInterface::setValue(const float value) {
    if (!qFuzzyCompare(iValue_, value)) {
        iValue_ =  value;
        emit valueChanged();
        qDebug() << "setValue: " + QString::number(iValue_);
    }
}

float sow::ParameterInterface::value() const {
    return iValue_;
}

void sow::ParameterInterface::setFixed(const bool fixed) {
    if (iFixed_ != fixed) {
        iFixed_ =  fixed;
        emit fixedChanged();
        qDebug() << "setFixed: " + QString::number(iFixed_);
    }
}

bool sow::ParameterInterface::fixed() const {
    return iFixed_;
}

void sow::ParameterInterface::setScaled(const bool scaled) {
    if (iScaled_ != scaled) {
        iScaled_ =  scaled;
        emit scaledChanged();
        qDebug() << "setScaled: " + QString::number(iScaled_);
    }
}

bool sow::ParameterInterface::scaled() const {
    return iScaled_;
}

void sow::ParameterInterface::setScaleLo(const float scaleLo) {
    if (!qFuzzyCompare(iScaleLo_, scaleLo)) {
        iScaleLo_ =  scaleLo;
        emit scaleLoChanged();
        qDebug() << "setScaleLo: " + QString::number(iScaleLo_);
    }
}

float sow::ParameterInterface::scaleLo() const {
    return iScaleLo_;
}

void sow::ParameterInterface::setScaleHi(const float scaleHi) {
    if (!qFuzzyCompare(iScaleHi_, scaleHi)) {
        iScaleHi_ =  scaleHi;
        emit scaleHiChanged();
        qDebug() << "setScaleHi: " + QString::number(iScaleHi_);
    }
}

float sow::ParameterInterface::scaleHi() const {
    return iScaleHi_;
}

void sow::ParameterInterface::setScaleExp(const float scaleExp) {
    if (!qFuzzyCompare(iScaleExp_, scaleExp)) {
        iScaleExp_ =  scaleExp;
        emit scaleExpChanged();
        qDebug() << "setScaleExp: " + QString::number(iScaleExp_);
    }
}

float sow::ParameterInterface::scaleExp() const {
    return iScaleExp_;
}

void sow::ParameterInterface::setMap(const QString map) {
    if (iMap_ != map) {
        iMap_ = map;
        emit nameChanged();
        qDebug() << "setMap: " + iMap_;
    }
}

QString sow::ParameterInterface::map() const {
    return iMap_;
}

} // Namespace sow.
