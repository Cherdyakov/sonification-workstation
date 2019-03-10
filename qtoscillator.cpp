#include "qtoscillator.h"

namespace sow {

QtOscillator::QtOscillator(QObject *parent) : QtSynthItem(parent)
{
    frequencyInterface_ = new ParameterInterface(this);
    frequency_ = new Parameter(this);
    frequency_->connectInterface(frequencyInterface_);
}

ParameterInterface* QtOscillator::frequencyInterface() const
{
    return frequencyInterface_;
}

} // End namespace sow.
