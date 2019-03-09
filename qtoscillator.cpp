#include "qtoscillator.h"

namespace sow {

QtOscillator::QtOscillator(QObject *parent) : QtSynthItem(parent)
{
    frequency_ = new SowParameter(this);
}

SowParameter* QtOscillator::frequency() const
{
    return frequency_;
}

} // End namespace sow.
