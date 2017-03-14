#include "synthitem.h"
#include "Gamma.h"

namespace son {

SynthItem::SynthItem()
{
    muted = false;
    dataItem = NULL;
}

void SynthItem::setIndexes(std::vector<int> indexes)
{

}

void SynthItem::mute(bool mute)
{

}

void SynthItem::removeChild(SynthItem *item)
{

}

void SynthItem::addChild(SynthItem *item, SynthItem::SON_CHILD_TYPE type)
{

}

float SynthItem::process(float in)
{

}

float SynthItem::process()
{

}

void SynthItem::setDataItem(std::vector<double> *data)
{
    dataItem = data;
}

} //namespace son
