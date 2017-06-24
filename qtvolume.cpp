#include "qtvolume.h"

using namespace son;

QtVolume::QtVolume(Volume *volume, QObject *parent) : QtSynthItem(parent)
{
    volume_ = volume;
}

SynthItem *QtVolume::implementation()
{
    return volume_;
}

void QtVolume::deleteItem()
{
    volume_->delete_item();
}

void QtVolume::addParent(QtSynthItem *parent)
{
    volume_->add_parent(parent->implementation());
}

void QtVolume::removeParent(QtSynthItem *parent)
{
volume_->remove_parent(parent->implementation());
}

bool QtVolume::addChild(QtSynthItem *child, QtSynthItem::PARAMETER param)
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

void QtVolume::setVolumeScaleVals(double low, double high, double exp)
{
    volume_->set_volume_scale_vals(low, high, exp);
}
