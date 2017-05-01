#include "qtmodulator.h"

QtModulator::QtModulator(SynthItem *item, QObject *parent)
{
    this->setParent(parent);
    synthItem = item;
}

void QtModulator::setModulationParameter(PARAMETER parameter)
{
    dynamic_cast<son::Modulator*>(synthItem)->set_mod_type((SynthItem::PARAMETER)parameter);
}

void QtModulator::setDepth(double depth)
{
    dynamic_cast<son::Modulator*>(synthItem)->set_depth(depth);
}

void QtModulator::setUseFixedDepth(bool fixed)
{
    dynamic_cast<son::Modulator*>(synthItem)->set_depth_fixed(fixed);
}

void QtModulator::setUseDepthScaling(bool scaling)
{
    dynamic_cast<son::Modulator*>(synthItem)->set_depth_scaled(scaling);
}

void QtModulator::setDepthScalingVals(double low, double high, double exp)
{
    dynamic_cast<son::Modulator*>(synthItem)->set_depth_scale_vals(low, high, exp);
}
