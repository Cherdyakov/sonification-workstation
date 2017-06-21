#include "qtenvelope.h"

QtEnvelope::QtEnvelope(Envelope *envelope, QObject *parent) : QtSynthItem(parent)
{
    envelope_ = envelope;
}

SynthItem *QtEnvelope::implementation()
{
    return envelope_;
}

void QtEnvelope::deleteItem()
{
    envelope_->delete_item();
}

void QtEnvelope::addParent(QtSynthItem *parent)
{
    envelope_->add_parent(parent->implementation());
}

void QtEnvelope::removeParent(QtSynthItem *parent)
{
    envelope_->remove_parent(parent->implementation());
}

bool QtEnvelope::addChild(QtSynthItem *child, QtSynthItem::PARAMETER param)
{
    return envelope_->add_child(child->implementation(), (SynthItem::PARAMETER)param);
}

void QtEnvelope::removeChild(QtSynthItem *child)
{
    envelope_->remove_child(child->implementation());
}

void QtEnvelope::mute(bool mute)
{
    envelope_->mute(mute);
}

void QtEnvelope::setAttack(double att)
{
    envelope_->set_attack(att);
}

void QtEnvelope::setAttackFixed(bool fixed)
{
    envelope_->set_attack_fixed(fixed);
}

void QtEnvelope::setAttackIndexes(QVector<int> indexes)
{
    std::vector<int> vec = indexes.toStdVector();
    envelope_->set_attack_indexes(vec);
}

void QtEnvelope::setAttackScaled(bool scaled)
{
    envelope_->set_attack_scaled(scaled);
}

void QtEnvelope::setAttackScaleVals(double low, double high, double exp)
{
    envelope_->set_attack_scale_vals(low, high, exp);
}

void QtEnvelope::setDecay(double att)
{
    envelope_->set_decay(att);
}

void QtEnvelope::setDecayFixed(bool fixed)
{
    envelope_->set_decay_fixed(fixed);
}

void QtEnvelope::setDecayIndexes(QVector<int> indexes)
{
    std::vector<int> vec = indexes.toStdVector();
    envelope_->set_decay_indexes(vec);
}

void QtEnvelope::setDecayScaled(bool scaled)
{
    envelope_->set_decay_scaled(scaled);
}

void QtEnvelope::setDecayScaleVals(double low, double high, double exp)
{
    envelope_->set_decay_scale_vals(low, high, exp);
}
