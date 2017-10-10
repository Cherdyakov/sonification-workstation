#include "qtpanner.h"

using namespace son;

QtPanner::QtPanner(Panner *panner, QObject *parent) : QtSynthItem(parent)
{
    panner_ = panner;
}

SynthItem *QtPanner::implementation()
{
    return panner_;
}

void QtPanner::deleteSelf()
{
    panner_->delete_self();
}

void QtPanner::addParent(QtSynthItem *parent)
{
    panner_->add_parent(parent->implementation());
}

void QtPanner::removeParent(QtSynthItem *parent)
{
    panner_->remove_parent(parent->implementation());
}

bool QtPanner::addChild(QtSynthItem *child, QtSynthItem::QT_PARAMETER param)
{
    return panner_->add_child(child->implementation(), (SynthItem::PARAMETER)param);
}

void QtPanner::removeChild(QtSynthItem *child)
{
    panner_->remove_child(child->implementation());
}

void QtPanner::mute(bool mute)
{
    panner_->mute(mute);
}

void QtPanner::setPan(double pan)
{
    panner_->set_pan(pan);
}

void QtPanner::setPanFixed(bool fixed)
{
    panner_->set_pan_fixed(fixed);
}

void QtPanner::setPanIndexes(QVector<int> indexes)
{
    std::vector<int> vec = indexes.toStdVector();
    panner_->set_pan_indexes(vec);
}

void QtPanner::setPanScaled(bool scaled)
{
    panner_->set_pan_scaled(scaled);
}

void QtPanner::setPanScaleLow(double low)
{
    panner_->set_pan_scale_low(low);
}

void QtPanner::setPanScaleHigh(double high)
{
    panner_->set_pan_scale_high(high);
}

void QtPanner::setPanScaleExponent(double exponent)
{
    panner_->set_pan_scale_exponent(exponent);
}

bool QtPanner::getMute()
{
    bool muted = panner_->get_mute();
    return muted;
}

double QtPanner::getPan()
{
    double pan = panner_->get_pan();
    return pan;
}

bool QtPanner::getPanFixed()
{
    bool fixed = panner_->get_pan_fixed();
    return fixed;
}

QVector<int> QtPanner::getPanIndexes()
{
    std::vector<int> vec = panner_->get_pan_indexes();
    QVector<int> indexes = QVector<int>::fromStdVector(vec);
    return indexes;
}

bool QtPanner::getPanScaled()
{
    bool scaled = panner_->get_pan_scaled();
    return scaled;
}

double QtPanner::getPanScaleLow()
{
    double low = panner_->get_pan_scale_low();
    return low;
}

double QtPanner::getPanScaleHigh()
{
    double high = panner_->get_pan_scale_high();
    return high;
}

double QtPanner::getPanScaleExponent()
{
    double exponent = panner_->get_pan_scale_exponent();
    return exponent;
}
