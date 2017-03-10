#include "qtsynthitem.h"

using namespace son;

QtSynthItem::QtSynthItem(QObject *parent) : QObject(parent)
{

}

float QtSynthItem::process()
{
    float s = 0;
    s = synthItem.process();
    return s;
}

float QtSynthItem::process(float in)
{
    float s = 0;
    s = synthItem.process(s);
    return s;
}

void QtSynthItem::setDataItem(std::vector<double> *data)
{
    synthItem.setDataItem(data);
}

void QtSynthItem::addChild(SynthItem *item, SynthItem::SON_CHILD_TYPE type)
{
    synthItem.addChild(item, type);
}

void QtSynthItem::removeChild(SynthItem *item)
{
    synthItem.removeChild(item);
}

void QtSynthItem::mute(bool mute)
{
    synthItem.mute(mute);
}
