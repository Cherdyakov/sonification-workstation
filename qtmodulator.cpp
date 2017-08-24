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

bool QtModulator::addChild(QtSynthItem *child, QtSynthItem::QT_PARAMETER param)
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

void QtModulator::setFreqScaleLow(double low)
{
    modulator_->set_freq_scale_low(low);
}

void QtModulator::setFreqScaleHigh(double high)
{
    modulator_->set_freq_scale_high(high);
}

void QtModulator::setFreqScaleExponent(double exponent)
{
    modulator_->set_freq_scale_exponent(exponent);
}

void QtModulator::setModType(QtSynthItem::QT_PARAMETER parameter)
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

void QtModulator::setDepthScaleLow(double low)
{
    modulator_->set_depth_scale_low(low);
}

void QtModulator::setDepthScaleHigh(double high)
{
    modulator_->set_depth_scale_high(high);
}

void QtModulator::setDepthScaleExponent(double exponent)
{
    modulator_->set_depth_scale_exponent(exponent);
}

bool QtModulator::getMute()
{
    bool mute = modulator_->get_mute();
    return mute;
}

double QtModulator::getFreq()
{
    double freq = modulator_->get_freq();
    return freq;
}

bool QtModulator::getFreqFixed()
{
    bool fixed = modulator_->get_freq_fixed();
    return fixed;
}

QVector<int> QtModulator::getFreqIndexes()
{
    std::vector<int> vec = modulator_->get_freq_indexes();
    QVector<int> indexes = QVector<int>::fromStdVector(vec);
    return indexes;
}

bool QtModulator::getFreqScaled()
{
    bool scaled = modulator_->get_freq_scaled();
    return scaled;
}

double QtModulator::getFreqScaleLow()
{
    double low = modulator_->get_freq_scale_low();
    return low;
}

double QtModulator::getFreqScaleHigh()
{
    double high = modulator_->get_freq_scale_high();
    return high;
}

double QtModulator::getFreqScaleExponent()
{
    double exponent = modulator_->get_freq_scale_exponent();
    return exponent;
}

int QtModulator::getModType()
{
    QT_PARAMETER type = (QT_PARAMETER)modulator_->get_mod_type();
    return type;
}

double QtModulator::getDepth()
{
    double depth = modulator_->get_depth();
    return depth;
}

bool QtModulator::getDepthFixed()
{
    bool fixed = modulator_->get_depth_fixed();
    return fixed;
}

QVector<int> QtModulator::getDepthIndexes()
{
    std::vector<int> vec = modulator_->get_depth_indexes();
    QVector<int> indexes = QVector<int>::fromStdVector(vec);
    return indexes;
}

bool QtModulator::getDepthScaled()
{
    bool scaled = modulator_->get_depth_scaled();
    return scaled;
}

double QtModulator::getDepthScaleLow()
{
    double low = modulator_->get_depth_scale_low();
    return low;
}

double QtModulator::getDepthScaleHigh()
{
    double high = modulator_->get_depth_scale_high();
    return high;
}

double QtModulator::getDepthScaleExponent()
{
    double exponent = modulator_->get_depth_scale_exponent();
    return exponent;
}
