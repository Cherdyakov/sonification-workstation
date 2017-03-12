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
    float s = 0;
    s = synthItem->process();
    return s;
}

float QtSynthItem::process(float in)
{
    float s = 0;
    s = synthItem->process(in);
    return s;
}

void QtSynthItem::setDataItem(QVector<double> *data)
{
    std::vector<double> vec = data->toStdVector();
    synthItem->setDataItem(&vec);
}

void QtSynthItem::addChild(QtSynthItem *child, CHILD_TYPE type)
{
    synthItem->addChild(child->implementation(), (SynthItem::SON_CHILD_TYPE)type);
}

void QtSynthItem::removeChild(QtSynthItem *child)
{
    synthItem->removeChild(child->implementation());
}

void QtSynthItem::mute(bool mute)
{
    synthItem->mute(mute);
}

void QtSynthItem::setIndexes(QVector<int> indexes)
{
    std::vector<int> vec = indexes.toStdVector();
    synthItem->setIndexes(vec);
}
