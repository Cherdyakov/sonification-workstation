#include "qtmodulator.h"

QtModulator::QtModulator(SynthItem *item, QObject *parent)
{
    this->setParent(parent);
    synthItem = item;
}

void QtModulator::setModulationParameter(PARAMETER parameter)
{
    dynamic_cast<son::Modulator*>(synthItem)->modulationType((SynthItem::PARAMETER)parameter);
}

void QtModulator::setDepth(double depth)
{
    dynamic_cast<son::Modulator*>(synthItem)->depth_(depth);
}

void QtModulator::setUseFixedDepth(bool fixed)
{
    dynamic_cast<son::Modulator*>(synthItem)->fixed_depth(fixed);
}

void QtModulator::setUseDepthScaling(bool scaling)
{
    dynamic_cast<son::Modulator*>(synthItem)->scale_depth(scaling);
}

void QtModulator::setDepthScalingVals(double low, double high, double exp)
{
    dynamic_cast<son::Modulator*>(synthItem)->depth_scale_values(low, high, exp);
}
