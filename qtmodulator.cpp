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

}

void QtModulator::setUseDepthScaling(bool scaling)
{

}

void QtModulator::setDepthScalingVals(double low, double high, double exp)
{

}
