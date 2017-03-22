#include "synthitem.h"
#include "Gamma.h"

namespace son {

SynthItem::SynthItem()
{
    muted = false;
    dataItem = NULL;
}

void SynthItem::removeParent(SynthItem *parent)
{
    if(parent)
    {
        parents.erase(std::remove(parents.begin(), parents.end(), parent), parents.end());
    }
}

void SynthItem::addParent(SynthItem *parent)
{
    if(parent)
    {
        if(std::find(parents.begin(), parents.end(), parent) != parents.end()) {
            return;
        } else {
            parents.push_back(parent);
        }
    }
}

void SynthItem::setDataItem(std::vector<double> *data)
{
    dataItem = data;
}

} //namespace son
