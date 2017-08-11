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

bool QtEnvelope::addChild(QtSynthItem *child, QtSynthItem::QT_PARAMETER param)
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

void QtEnvelope::setAttackScaleLow(double low)
{
    envelope_->set_attack_scale_low(low);
}

void QtEnvelope::setAttackScaleHigh(double high)
{
    envelope_->set_attack_scale_high(high);
}

void QtEnvelope::setAttackScaleExponent(double exponent)
{
    envelope_->set_attack_scale_exponent(exponent);
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

void QtEnvelope::setDecayScaleLow(double low)
{
    envelope_->set_decay_scale_low(low);
}

void QtEnvelope::setDecayScaleHigh(double high)
{
    envelope_->set_decay_scale_high(high);
}

void QtEnvelope::setDecayScaleExponent(double exponent)
{
    envelope_->set_decay_scale_exponent(exponent);
}

bool QtEnvelope::getMute()
{
    bool muted = envelope_->get_mute();
    return muted;
}

double QtEnvelope::getAttack()
{
    double attack = envelope_->get_attack();
    return attack;
}

bool QtEnvelope::getAttackFixed()
{
    bool fixed = envelope_->get_attack_fixed();
    return fixed;
}

QVector<int> QtEnvelope::getAttackIndexes()
{
    std::vector<int> vec = envelope_->get_attack_indexes();
    QVector<int> indexes = QVector<int>::fromStdVector(vec);
    return indexes;
}

bool QtEnvelope::getAttackScaled()
{
    bool scaled = envelope_->get_attack_scaled();
    return scaled;
}

double QtEnvelope::getAttackScaleLow()
{
    double low = envelope_->get_attack_scale_low();
    return low;
}

double QtEnvelope::getAttackScaleHigh()
{
    double high = envelope_->get_attack_scale_high();
    return high;
}

double QtEnvelope::getAttackScaleExponent()
{
    double exponent = envelope_->get_attack_scale_exponent();
    return exponent;
}

double QtEnvelope::getDecay()
{
    double decay = envelope_->get_decay();
    return decay;
}

bool QtEnvelope::getDecayFixed()
{
    bool fixed = envelope_->get_decay_fixed();
    return fixed;
}

QVector<int> QtEnvelope::getDecayIndexes()
{
    std::vector<int> vec = envelope_->get_decay_indexes();
    QVector<int> indexes = QVector<int>::fromStdVector(vec);
    return indexes;
}

bool QtEnvelope::getDecayScaled()
{
    bool scaled = envelope_->get_decay_scaled();
    return scaled;
}

double QtEnvelope::getDecayScaleLow()
{
    double low = envelope_->get_decay_scale_low();
    return low;
}

double QtEnvelope::getDecayScaleHigh()
{
    double high = envelope_->get_decay_scale_high();
    return high;
}

double QtEnvelope::getDecayScaleExponent()
{
    double exponent = envelope_->get_decay_scale_exponent();
    return exponent;
}
