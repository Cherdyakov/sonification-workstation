#include "qtnoise.h"

QtNoise::QtNoise(Noise *noise, QObject *parent) : QtSynthItem(parent)
{
    noise_ = noise;
}

SynthItem *QtNoise::implementation()
{
    return noise_;
}

void QtNoise::deleteItem()
{
    noise_->delete_item();
}

void QtNoise::addParent(QtSynthItem *parent)
{
    noise_->add_parent(parent->implementation());
}

void QtNoise::removeParent(QtSynthItem *parent)
{
    noise_->remove_parent(parent->implementation());
}

bool QtNoise::addChild(QtSynthItem *child, QtSynthItem::PARAMETER param)
{
    return noise_->add_child(child->implementation(), (SynthItem::PARAMETER)param);
}

void QtNoise::removeChild(QtSynthItem *child)
{
    noise_->remove_child(child->implementation());
}

void QtNoise::mute(bool mute)
{
    noise_->mute(mute);
}

void QtNoise::setNoise(int noise)
{
    noise_->set_noise((SynthItem::NOISE)noise);
}
