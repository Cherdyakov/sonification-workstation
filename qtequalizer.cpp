#include "qtequalizer.h"

using namespace son;

QtEqualizer::QtEqualizer(Equalizer *equalizer, QObject *parent) : QtSynthItem(parent)
{
    equalizer_ = equalizer;
}

SynthItem *QtEqualizer::implementation()
{
    return equalizer_;
}

void QtEqualizer::deleteItem()
{
    equalizer_->delete_item();
}

void QtEqualizer::addParent(QtSynthItem *parent)
{
    equalizer_->add_parent(parent->implementation());
}

void QtEqualizer::removeParent(QtSynthItem *parent)
{
    equalizer_->remove_parent(parent->implementation());
}

bool QtEqualizer::addChild(QtSynthItem *child, QtSynthItem::PARAMETER param)
{
    return equalizer_->add_child(child->implementation(), (SynthItem::PARAMETER)param);
}

void QtEqualizer::removeChild(QtSynthItem *child)
{
    equalizer_->remove_child(child->implementation());
}

void QtEqualizer::mute(bool mute)
{
    equalizer_->mute(mute);
}

void QtEqualizer::setFrequency(double frequency)
{
    equalizer_->set_frequency(frequency);
}

void QtEqualizer::setFrequencyFixed(bool fixed)
{
    equalizer_->set_frequency_fixed(fixed);
}

void QtEqualizer::setFrequencyIndexes(QVector<int> indexes)
{
    std::vector<int> vec = indexes.toStdVector();
    equalizer_->set_frequency_indexes(vec);
}

void QtEqualizer::setFrequencyScaled(bool scaled)
{
    equalizer_->set_frequency_scaled(scaled);
}

void QtEqualizer::setFrequencyScaleVals(double low, double high, double exp)
{
    equalizer_->set_frequency_scale_vals(low, high, exp);
}

void QtEqualizer::setResonance(double resonance)
{
    equalizer_->set_resonance(resonance);
}

void QtEqualizer::setResonanceFixed(bool fixed)
{
    equalizer_->set_resonance_fixed(fixed);
}

void QtEqualizer::setResonanceIndexes(QVector<int> indexes)
{
    std::vector<int> vec = indexes.toStdVector();
    equalizer_->set_resonance_indexes(vec);
}

void QtEqualizer::setResonanceScaled(bool scaled)
{
    equalizer_->set_resonance_scaled(scaled);
}

void QtEqualizer::setResonanceScaleVals(double low, double high, double exp)
{
    equalizer_->set_resonance_scale_vals(low, high, exp);
}

void QtEqualizer::setFilterType(SynthItem::FILTER_TYPE type)
{
    equalizer_->set_filter_type(type);
}
