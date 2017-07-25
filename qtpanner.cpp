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

void QtPanner::deleteItem()
{
    panner_->delete_item();
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

void QtPanner::setPanScaleVals(double low, double high, double exp)
{
    panner_->set_pan_scale_vals(low, high, exp);
}
