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

bool QtSynthItem::addChild(QtSynthItem *child, PARAMETER parameter)
{
    return synthItem->addChild(child->implementation(), (SynthItem::PARAMETER)parameter);
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

void QtSynthItem::setIndexes(QVector<int> indexes, PARAMETER parameter)
{
    if(!synthItem)
        return;

    std::vector<int> vec = indexes.toStdVector();
    synthItem->setIndexes(vec, (SynthItem::PARAMETER)parameter);
}

void QtSynthItem::deleteItem()
{
    synthItem->deleteItem();
}
