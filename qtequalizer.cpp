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

void QtEqualizer::deleteSelf()
{
    equalizer_->delete_self();
}

void QtEqualizer::addParent(QtSynthItem *parent)
{
    equalizer_->add_parent(parent->implementation());
}

void QtEqualizer::removeParent(QtSynthItem *parent)
{
    equalizer_->remove_parent(parent->implementation());
}

bool QtEqualizer::addChild(QtSynthItem *child, QtSynthItem::QT_PARAMETER param)
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

void QtEqualizer::setFrequencyScaleLow(double low)
{
    equalizer_->set_frequency_scale_low(low);
}

void QtEqualizer::setFrequencyScaleHigh(double high)
{
    equalizer_->set_frequency_scale_high(high);
}

void QtEqualizer::setFrequencyScaleExponent(double exponent)
{
    equalizer_->set_frequency_scale_exponent(exponent);
}

void QtEqualizer::setResonance(double resonance)
{
    equalizer_->set_resonance(resonance);
}

void QtEqualizer::setResonanceFixed(bool fixed)
{
    equalizer_->set_resonance_fixed(fixed);
}

void QtEqualizer::setResonanceScaleLow(double low)
{
    equalizer_->set_resonance_scale_low(low);
}

void QtEqualizer::setResonanceScaleHigh(double high)
{
    equalizer_->set_resonance_scale_high(high);
}

void QtEqualizer::setResonanceScaleExponent(double exponent)
{
    equalizer_->set_resonance_scale_exponent(exponent);
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

void QtEqualizer::setFilterType(QT_FILTER_TYPES type)
{
    equalizer_->set_filter_type((SynthItem::FILTER_TYPE)type);
}

bool QtEqualizer::getMute()
{
    bool muted = equalizer_->get_mute();
    return muted;
}

double QtEqualizer::getFrequency()
{
    double frequency = equalizer_->get_frequency();
    return frequency;
}

bool QtEqualizer::getFrequencyFixed()
{
    bool fixed = equalizer_->get_frequency_fixed();
    return fixed;
}

QVector<int> QtEqualizer::getFrequencyIndexes()
{
    std::vector<int> vec = equalizer_->get_frequency_indexes();
    QVector<int> indexes = QVector<int>::fromStdVector(vec);
    return indexes;
}

bool QtEqualizer::getFrequencyScaled()
{
    bool scaled = equalizer_->get_frequency_scaled();
    return scaled;
}

double QtEqualizer::getFrequencyScaleLow()
{
    double low = equalizer_->get_frequency_scale_low();
    return low;
}

double QtEqualizer::getFrequencyScaleHigh()
{
    double high = equalizer_->get_frequency_scale_high();
    return high;
}

double QtEqualizer::getFrequencyScaleExponent()
{
    double exponent = equalizer_->get_frequency_scale_exponent();
    return exponent;
}

double QtEqualizer::getResonance()
{
    double resonance = equalizer_->get_resonance();
    return resonance;
}

bool QtEqualizer::getResonanceFixed()
{
    bool fixed = equalizer_->get_resonance_fixed();
    return fixed;
}

QVector<int> QtEqualizer::getResonanceIndexes()
{
    std::vector<int> vec = equalizer_->get_resonance_indexes();
    QVector<int> indexes = QVector<int>::fromStdVector(vec);
    return indexes;
}

bool QtEqualizer::getResonanceScaled()
{
    bool scaled = equalizer_->get_resonance_scaled();
    return scaled;
}

double QtEqualizer::getResonanceScaleLow()
{
    double low = equalizer_->get_resonance_scale_low();
    return low;
}

double QtEqualizer::getResonanceScaleHigh()
{
    double high = equalizer_->get_resonance_scale_high();
    return high;
}

double QtEqualizer::getResonanceScaleExponent()
{
    double exponent = equalizer_->get_resonance_scale_exponent();
    return exponent;
}
