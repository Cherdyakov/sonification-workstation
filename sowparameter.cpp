#include "sowparameter.h"
#include <QDebug>

namespace sow {

SowParameter::SowParameter(QObject *parent) : QObject(parent)
{

}


void sow::SowParameter::setName(const QString name) {
    if (name_ != name) {
        name_ = name;
        emit nameChanged();
    }
    qDebug() << "setName: " + name_;
}

QString sow::SowParameter::name() const {
    return name_;
}

void sow::SowParameter::setType(const SowEnums::PARAMETER type) {
    if (type_ != type) {
        type_ = type;
        emit typeChanged();
    }
}

SowEnums::PARAMETER sow::SowParameter::type() const {
    return type_;
}

void sow::SowParameter::setValue(const float value) {
    if (!qFuzzyCompare(value_, value)) {
        value_ =  value;
        emit valueChanged();
        qDebug() << "setValue: " + QString::number(value_);
    }
}

float sow::SowParameter::value() const {
    return value_;
}

void sow::SowParameter::setFixed(const bool fixed) {
    if (fixed_ != fixed) {
        fixed_ =  fixed;
        emit fixedChanged();
        qDebug() << "setFixed: " + QString::number(fixed_);
    }
}

bool sow::SowParameter::fixed() const {
    return fixed_;
}

void sow::SowParameter::setScaled(const bool scaled) {
    if (scaled_ != scaled) {
        scaled_ =  scaled;
        emit scaledChanged();
        qDebug() << "setScaled: " + QString::number(scaled_);
    }
}

bool sow::SowParameter::scaled() const {
    return scaled_;
}

void sow::SowParameter::setScaleLo(const float scaleLo) {
    if (!qFuzzyCompare(scaleLo_, scaleLo)) {
        scaleLo_ =  scaleLo;
        emit scaleLoChanged();
        qDebug() << "setScaleLo: " + QString::number(scaleLo_);
    }
}

float sow::SowParameter::scaleLo() const {
    return scaleLo_;
}

void sow::SowParameter::setScaleHi(const float scaleHi) {
    if (!qFuzzyCompare(scaleHi_, scaleHi)) {
        scaleHi_ =  scaleHi;
        emit scaleHiChanged();
        qDebug() << "setScaleHi: " + QString::number(scaleHi_);
    }
}

float sow::SowParameter::scaleHi() const {
    return scaleHi_;
}

void sow::SowParameter::setScaleExp(const float scaleExp) {
    if (!qFuzzyCompare(scaleExp_, scaleExp)) {
        scaleExp_ =  scaleExp;
        emit scaleExpChanged();
        qDebug() << "setScaleExp: " + QString::number(scaleExp_);
    }
}

float sow::SowParameter::scaleExp() const {
    return scaleExp_;
}

void sow::SowParameter::setMap(const QString map) {
    if (map_ != map) {
        map_ = map;
        emit nameChanged();
        qDebug() << "setMap: " + map_;
    }
}

QString sow::SowParameter::map() const {
    return map_;
}

} // Namespace sow.
