#include "synthitem.h"
#include "Gamma.h"

namespace son {

SynthItem::SynthItem()
{
    muted = false;
    dataItem = NULL;
}

void SynthItem::setDataItem(std::vector<double> *data)
{
    dataItem = data;
}

} //namespace son
