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

void QtSynthItem::addChild(QtSynthItem *child, SON_CHILD_TYPE type)
{
    synthItem->addChild(child, type);
}

void QtSynthItem::removeChild(QtSynthItem *child)
{
    synthItem->removeChild(child);
}

void QtSynthItem::mute(bool mute)
{
    synthItem->mute(mute);
}

void QtSynthItem::setIndexes(QVector<int> indexes)
{
    synthItem->setIndexes(indexes);
}
