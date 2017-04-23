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
    return synthItem->process();
}

float QtSynthItem::process(float in)
{
    return synthItem->process(in);
}

bool QtSynthItem::addChild(QtSynthItem *child)
{
    return synthItem->addChild(child->implementation());
}

void QtSynthItem::removeChild(QtSynthItem *child)
{
    synthItem->removeChild(child->implementation());
}

void QtSynthItem::addParent(QtSynthItem *parent)
{
    if(!parent || !synthItem)
        return;

    synthItem->addParent(parent->implementation());
}

void QtSynthItem::removeParent(QtSynthItem *parent)
{
    if(!parent || !synthItem)
        return;

    synthItem->removeParent(parent->implementation());
}

void QtSynthItem::mute(bool mute)
{
    if(!synthItem)
        return;

    synthItem->mute(mute);
}

void QtSynthItem::setIndexes(QVector<int> indexes)
{
    if(!synthItem)
        return;

    std::vector<int> vec = indexes.toStdVector();
    synthItem->setIndexes(vec);
}
