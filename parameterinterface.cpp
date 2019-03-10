#include "parameterinterface.h"
#include <QDebug>

namespace sow {

ParameterInterface::ParameterInterface(QObject *parent) : QObject(parent)
{
    setFixed(true);
    setScaleLo(900);
}


void sow::ParameterInterface::setName(const QString name) {
    if (name_ != name) {
        name_ = name;
        emit nameChanged();
    }
    qDebug() << "setName: " + name_;
}

QString sow::ParameterInterface::name() const {
    return name_;
}

void sow::ParameterInterface::setType(const SowEnums::PARAMETER type) {
    if (type_ != type) {
        type_ = type;
        emit typeChanged();
    }
}

SowEnums::PARAMETER sow::ParameterInterface::type() const {
    return type_;
}

void sow::ParameterInterface::setValue(const float value) {
    if (!qFuzzyCompare(value_, value)) {
        value_ =  value;
        emit valueChanged();
        qDebug() << "setValue: " + QString::number(value_);
    }
}

float sow::ParameterInterface::value() const {
    return value_;
}

void sow::ParameterInterface::setFixed(const bool fixed) {
    if (fixed_ != fixed) {
        fixed_ =  fixed;
        emit fixedChanged();
        qDebug() << "setFixed: " + QString::number(fixed_);
    }
}

bool sow::ParameterInterface::fixed() const {
    return fixed_;
}

void sow::ParameterInterface::setScaled(const bool scaled) {
    if (scaled_ != scaled) {
        scaled_ =  scaled;
        emit scaledChanged();
        qDebug() << "setScaled: " + QString::number(scaled_);
    }
}

bool sow::ParameterInterface::scaled() const {
    return scaled_;
}

void sow::ParameterInterface::setScaleLo(const float scaleLo) {
    if (!qFuzzyCompare(scaleLo_, scaleLo)) {
        scaleLo_ =  scaleLo;
        emit scaleLoChanged();
        qDebug() << "setScaleLo: " + QString::number(scaleLo_);
    }
}

float sow::ParameterInterface::scaleLo() const {
    return scaleLo_;
}

void sow::ParameterInterface::setScaleHi(const float scaleHi) {
    if (!qFuzzyCompare(scaleHi_, scaleHi)) {
        scaleHi_ =  scaleHi;
        emit scaleHiChanged();
        qDebug() << "setScaleHi: " + QString::number(scaleHi_);
    }
}

float sow::ParameterInterface::scaleHi() const {
    return scaleHi_;
}

void sow::ParameterInterface::setScaleExp(const float scaleExp) {
    if (!qFuzzyCompare(scaleExp_, scaleExp)) {
        scaleExp_ =  scaleExp;
        emit scaleExpChanged();
        qDebug() << "setScaleExp: " + QString::number(scaleExp_);
    }
}

float sow::ParameterInterface::scaleExp() const {
    return scaleExp_;
}

void sow::ParameterInterface::setMap(const QString map) {
    if (map_ != map) {
        map_ = map;
        emit nameChanged();
        qDebug() << "setMap: " + map_;
    }
}

QString sow::ParameterInterface::map() const {
    return map_;
}

} // Namespace sow.
