#include "qtmodulator.h"

QtModulator::QtModulator(Modulator *modulator, QObject *parent) : QtSynthItem(parent)
{
    modulator_ = modulator;
}

SynthItem *QtModulator::implementation()
{
    return modulator_;
}

void QtModulator::deleteItem()
{
    modulator_->delete_item();
}

void QtModulator::addParent(QtSynthItem *parent)
{
    modulator_->add_parent(parent->implementation());
}

void QtModulator::removeParent(QtSynthItem *parent)
{
    modulator_->remove_parent(parent->implementation());
}

bool QtModulator::addChild(QtSynthItem *child, QtSynthItem::PARAMETER param)
{
    return modulator_->add_child(child->implementation(), (SynthItem::PARAMETER)param);
}

void QtModulator::removeChild(QtSynthItem *child)
{
    modulator_->remove_child(child->implementation());
}

void QtModulator::mute(bool mute)
{
    modulator_->mute(mute);
}

void QtModulator::setFreq(double freq)
{
    modulator_->set_freq(freq);
}

void QtModulator::setFreqFixed(bool fixed)
{
    modulator_->set_freq_fixed(fixed);
}

void QtModulator::setFreqIndexes(QVector<int> indexes)
{
    std::vector<int> vec = indexes.toStdVector();
    modulator_->set_freq_indexes(vec);
}

void QtModulator::setFreqScaled(bool scaled)
{
    modulator_->set_freq_scaled(scaled);
}

void QtModulator::setFreqScaleVals(double low, double high, double exp)
{
    modulator_->set_freq_scale_vals(low, high, exp);
}

void QtModulator::setModType(QtSynthItem::PARAMETER parameter)
{
    modulator_->set_mod_type((SynthItem::PARAMETER)parameter);
}

void QtModulator::setDepth(double depth)
{
    modulator_->set_depth(depth);
}

void QtModulator::setDepthFixed(bool fixed)
{
    modulator_->set_depth_fixed(fixed);
}

void QtModulator::setDepthIndexes(QVector<int> indexes)
{
    std::vector<int> vec = indexes.toStdVector();
    modulator_->set_depth_indexes(vec);
}

void QtModulator::setDepthScaled(bool scaled)
{
    modulator_->set_depth_scaled(scaled);
}

void QtModulator::setDepthScaleVals(double low, double high, double exp)
{
    modulator_->set_depth_scale_vals(low, high, exp);
}

