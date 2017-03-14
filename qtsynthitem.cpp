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

void QtSynthItem::addChild(QtSynthItem *child, CHILD_TYPE type)
{
    (void)child;
    (void)type;
}

void QtSynthItem::removeChild(QtSynthItem *child)
{
    (void)child;
}

void QtSynthItem::mute(bool mute)
{
    (void)mute;
}

void QtSynthItem::setIndexes(QVector<int> indexes)
{
    (void)indexes;
}
