#include "qtoscillator.h"

namespace sow {

QtOscillator::QtOscillator(QObject *parent) : QtSynthItem(parent)
{
    frequency_ = new ParameterInterface(this);
}

ParameterInterface* QtOscillator::frequency() const
{
    return frequency_;
}

} // End namespace sow.
