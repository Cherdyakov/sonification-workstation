#include "qtmodulator.h"

QtModulator::QtModulator(SynthItem *item, QObject *parent)
{
    this->setParent(parent);
    synthItem = item;
}

void QtModulator::setModulationParameter(PARAMETER parameter)
{
    dynamic_cast<son::Modulator*>(synthItem)->setModulationType((SynthItem::PARAMETER)parameter);
}

void QtModulator::setDepth(double depth)
{
    dynamic_cast<son::Modulator*>(synthItem)->setDepth(depth);
}

void QtModulator::setUseFixedDepth(bool fixed)
{
    dynamic_cast<son::Modulator*>(synthItem)->setUseFixedDepth(fixed);
}

void QtModulator::setUseDepthScaling(bool scaling)
{
    dynamic_cast<son::Modulator*>(synthItem)->setUseDepthScaling(scaling);
}

void QtModulator::setDepthScalingVals(double low, double high, double exp)
{
    dynamic_cast<son::Modulator*>(synthItem)->setDepthScalingVals(low, high, exp);
}
