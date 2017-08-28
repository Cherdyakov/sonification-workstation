#include "qtsynthitem.h"

using namespace son;

QtSynthItem::QtSynthItem(QObject *parent) : QObject(parent)
{

}

SynthItem *QtSynthItem::implementation()
{
    return NULL;
}

void QtSynthItem::deleteSelf()
{

}

void QtSynthItem::addParent(QtSynthItem *parent)
{
    Q_UNUSED(parent);
}

void QtSynthItem::removeParent(QtSynthItem *parent)
{
    Q_UNUSED(parent);
}

bool QtSynthItem::addChild(QtSynthItem *child, QtSynthItem::QT_PARAMETER parameter)
{
    Q_UNUSED(child);
    Q_UNUSED(parameter);
    return NULL;
}

void QtSynthItem::removeChild(QtSynthItem *item)
{
    Q_UNUSED(item);
}

void QtSynthItem::mute(bool mute)
{
    Q_UNUSED(mute);
}

bool QtSynthItem::getMute()
{
    return NULL;
}

