#include "qtvolume.h"

using namespace sow;

QtVolume::QtVolume(Volume *volume, QObject *parent) : QtSynthItem(parent)
{
    volume_ = volume;
}

SynthItem *QtVolume::implementation()
{
    return volume_;
}

void QtVolume::deleteSelf()
{
    volume_->delete_self();
}

void QtVolume::addParent(QtSynthItem *parent)
{
    volume_->add_parent(parent->implementation());
}

void QtVolume::removeParent(QtSynthItem *parent)
{
volume_->remove_parent(parent->implementation());
}

bool QtVolume::addChild(QtSynthItem *child, QtSynthItem::QT_PARAMETER param)
{
    return volume_->add_child(child->implementation(), (SynthItem::PARAMETER)param);
}

void QtVolume::removeChild(QtSynthItem *child)
{
    volume_->remove_child(child->implementation());
}

void QtVolume::mute(bool mute)
{
    volume_->mute(mute);
}

void QtVolume::setVolume(double volume)
{
    volume_->set_volume(volume);
}

void QtVolume::setVolumeFixed(bool fixed)
{
    volume_->set_volume_fixed(fixed);
}

void QtVolume::setVolumeIndexes(QVector<int> indexes)
{
    std::vector<int> vec = indexes.toStdVector();
    volume_->set_volume_indexes(vec);
}

void QtVolume::setVolumeScaled(bool scaled)
{
    volume_->set_volume_scaled(scaled);
}

void QtVolume::setVolumeScaleLow(double low)
{
    volume_->set_volume_scale_low(low);
}

void QtVolume::setVolumeScaleHigh(double high)
{
    volume_->set_volume_scale_high(high);
}

void QtVolume::setVolumeScaleExponent(double exponent)
{
    volume_->set_volume_scale_exponent(exponent);
}

bool QtVolume::getMute()
{
    bool muted = volume_->get_mute();
    return muted;
}

double QtVolume::getVolume()
{
    double volume = volume_->get_volume();
    return volume;
}

bool QtVolume::getVolumeFixed()
{
    bool fixed = volume_->get_volume_fixed();
    return fixed;
}

QVector<int> QtVolume::getVolumeIndexes()
{
    std::vector<int> vec = volume_->get_volume_indexes();
    QVector<int> indexes = QVector<int>::fromStdVector(vec);
    return indexes;
}

bool QtVolume::getVolumeScaled()
{
    bool scaled = volume_->get_volume_scaled();
    return scaled;
}

double QtVolume::getVolumeScaleLow()
{
    double low = volume_->get_volume_scale_low();
    return low;
}

double QtVolume::getVolumeScaleHigh()
{
    double high = volume_->get_volume_scale_high();
    return high;
}

double QtVolume::getVolumeScaleExponent()
{
    double exponent = volume_->get_volume_scale_exponent();
    return exponent;
}
