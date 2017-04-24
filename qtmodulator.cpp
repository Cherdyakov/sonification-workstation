#include "qtmodulator.h"

QtModulator::QtModulator(SynthItem *item, QObject *parent)
{
    this->setParent(parent);
    synthItem = item;
}

void QtModulator::setModType(QtSynthItem::CHILD_TYPE childType)
{
    static_cast<son::Modulator*>(synthItem)->setModType((SynthItem::ITEM_CHILD_TYPE)childType);
}

void QtModulator::setDepth(double depth)
{
    static_cast<son::Modulator*>(synthItem)->setDepth(depth);
}
