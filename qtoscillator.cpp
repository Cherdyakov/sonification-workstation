#include "qtoscillator.h"

using namespace son;

QtOscillator::QtOscillator(Oscillator *oscillator, QObject *parent) : QtSynthItem(parent)
{
    oscillator_ = oscillator;
}

SynthItem *QtOscillator::implementation()
{
    return oscillator_;
}

void QtOscillator::deleteSelf()
{
    oscillator_->delete_self();
}

void QtOscillator::addParent(QtSynthItem *parent)
{
    oscillator_->add_parent(parent->implementation());
}

void QtOscillator::removeParent(QtSynthItem *parent)
{
    oscillator_->remove_parent(parent->implementation());
}

bool QtOscillator::addChild(QtSynthItem *child, QtSynthItem::QT_PARAMETER param)
{
    return oscillator_->add_child(child->implementation(), (SynthItem::PARAMETER)param);
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

void QtOscillator::setFreqScaleLow(double low)
{
    oscillator_->set_freq_scale_low(low);
}

void QtOscillator::setFreqScaleHigh(double high)
{
    oscillator_->set_freq_scale_high(high);
}

void QtOscillator::setFreqScaleExponent(double exponent)
{
    oscillator_->set_freq_scale_exponent(exponent);
}

bool QtOscillator::getMute()
{
    bool muted = oscillator_->get_mute();
    return muted;
}

double QtOscillator::getFreq()
{
    double freq = oscillator_->get_freq();
    return freq;
}

bool QtOscillator::getFreqFixed()
{
    bool fixed = oscillator_->get_freq_fixed();
    return fixed;
}

QList<int> QtOscillator::getFreqIndexes()
{
    std::vector<int> vec = oscillator_->get_freq_indexes();
    QList<int> indexes = vecToQList(vec);
    return indexes;
}

bool QtOscillator::getFreqScaled()
{
    bool scaled = oscillator_->get_freq_scaled();
    return scaled;
}

double QtOscillator::getFreqScaleLow()
{
    double low = oscillator_->get_freq_scale_low();
    return low;
}

double QtOscillator::getFreqScaleHigh()
{
    double high = oscillator_->get_freq_scale_high();
    return high;
}

double QtOscillator::getFreqScaleExponent()
{
    double exponent = oscillator_->get_freq_scale_exponent();
    return exponent;
}




