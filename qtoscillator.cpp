#include "qtoscillator.h"

using namespace sow;

QtOscillator::QtOscillator(QObject *parent) : QtSynthItem(parent)
{
    frequency_ = new SowParameter(this);
}

SowParameter* QtOscillator::frequency() const
{
    return frequency_;
}
