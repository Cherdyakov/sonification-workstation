#include "qtoscillator.h"

using namespace son;

QtOscillator::QtOscillator(Oscillator *item, QObject *parent) : QtSynthItem(parent)
{
    oscillator_ = item;
}

SynthItem *QtOscillator::implementation()
{
    return oscillator_;
}

void QtOscillator::deleteItem()
{
    oscillator_->delete_item();
}

void QtOscillator::addParent(QtSynthItem *parent)
{
    oscillator_->add_parent(parent->implementation());
}

void QtOscillator::removeParent(QtSynthItem *parent)
{
    oscillator_->remove_parent(parent->implementation());
}

bool QtOscillator::addChild(QtSynthItem *child, QtSynthItem::PARAMETER param)
{
    oscillator_->add_child(child->implementation(), (SynthItem::PARAMETER)param);
}

void QtOscillator::removeChild(QtSynthItem *child)
{
    oscillator_->remove_child(child->implementation());
}

void QtOscillator::mute(bool mute)
{
    oscillator_->mute(mute);
}

void QtOscillator::setFreq(double freq)
{
    oscillator_->set_freq(freq);
}

void QtOscillator::setFreqFixed(bool fixed)
{
    oscillator_->set_freq_fixed(fixed);
}

void QtOscillator::setFreqIndexes(QVector<int> indexes)
{
    std::vector<int> vec = indexes.toStdVector();
    oscillator_->set_freq_indexes(vec);
}

void QtOscillator::setFreqScaled(bool scaled)
{
    oscillator_->set_freq_scaled(scaled);
}

void QtOscillator::setFreqScaleVals(double low, double high, double exp)
{
    oscillator_->set_freq_scale_vals(low, high, exp);
}




