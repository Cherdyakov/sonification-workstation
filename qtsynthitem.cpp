#include "qtsynthitem.h"

using namespace son;

QtSynthItem::QtSynthItem(QObject *parent) : QObject(parent)
{
    synthItem = NULL;
}

SynthItem *QtSynthItem::implementation()
{
    return synthItem;
}

float QtSynthItem::process()
{
    if(!synthItem)
        return 0.0;

    return synthItem->process();
}

bool QtSynthItem::addChild(QtSynthItem *child, PARAMETER parameter)
{
    if(!synthItem)
        return false;

    return synthItem->add_child(child->implementation(), (SynthItem::PARAMETER)parameter);
}

void QtSynthItem::removeChild(QtSynthItem *child)
{
    if(!synthItem)
        return;

    synthItem->remove_child(child->implementation());
}

void QtSynthItem::addParent(QtSynthItem *parent)
{
    if(!parent || !synthItem)
        return;

    synthItem->add_parent(parent->implementation());
}

void QtSynthItem::removeParent(QtSynthItem *parent)
{
    if(!parent || !synthItem)
        return;

    synthItem->remove_parent(parent->implementation());
}

void QtSynthItem::mute(bool mute)
{
    if(!synthItem)
        return;

    synthItem->mute(mute);
}

void QtSynthItem::deleteItem()
{
    if(!synthItem)
        return;

    synthItem->delete_item();
}
