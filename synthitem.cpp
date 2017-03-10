#include "synthitem.h"
#include "Gamma.h"

namespace son {

SynthItem::SynthItem()
{
    muted = false;
}

float SynthItem::process()
{
    return 0.0;
}

float SynthItem::process(float in)
{
    return in;
}

void SynthItem::setDataItem(std::vector<double> *data)
{
    dataItem = data;
}

void SynthItem::addChild(SynthItem *item, SON_CHILD_TYPE type)
{
    (void)item;
    (void)type;
}

void SynthItem::removeChild(SynthItem *item)
{
    (void)item;
}

void SynthItem::mute(bool mute)
{
    muted = mute;
}

void SynthItem::setIndexes(std::vector<int> indexes)
{
    dataIndexes = indexes;
}

} //namespace son
