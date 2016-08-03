#include "synthitem.h"
#include "Gamma.h"

namespace son {

SynthItem::SynthItem(QObject *parent) : QObject(parent)
{

}

float SynthItem::process()
{
    return qrand();
}

float SynthItem::process(float in)
{
    return in;
}

} //namespace son
