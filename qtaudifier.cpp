#include "qtaudifier.h"

QtAudifier::QtAudifier(Audifier* item, QObject* parent) : QtSynthItem(parent)
{
    audifier_ = item;
}

SynthItem *QtAudifier::implementation()
{
    return audifier_;
}

void QtAudifier::deleteItem()
{
    audifier_->delete_item();
}

void QtAudifier::addParent(QtSynthItem *parent)
{
    audifier_->add_parent(parent->implementation());
}

void QtAudifier::removeParent(QtSynthItem *parent)
{
    audifier_->remove_parent(parent->implementation());
}

bool QtAudifier::addChild(QtSynthItem *child, QtSynthItem::PARAMETER param)
{
    return audifier_->add_child(child->implementation(), (SynthItem::PARAMETER)param);
}

void QtAudifier::removeChild(QtSynthItem *child)
{
    audifier_->remove_child(child->implementation());
}

void QtAudifier::mute(bool mute)
{
    audifier_->mute(mute);
}

