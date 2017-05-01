#include "qtoscillator.h"

using namespace son;

QtOscillator::QtOscillator(SynthItem *item, QObject *parent) : QtSynthItem(parent)
{
    synthItem = item;
}

void QtOscillator::setFixedFreq(double freq)
{
   dynamic_cast<Oscillator*>(synthItem)->set_freq_fixed(freq);
}

void QtOscillator::setUseFixedFreq(bool fixed)
{
   dynamic_cast<Oscillator*>(synthItem)->set_freq_fixed(fixed);
}

void QtOscillator::setUseFreqScaling(bool scaling)
{
   dynamic_cast<Oscillator*>(synthItem)->set_freq_scaled(scaling);
}

void QtOscillator::setFreqScalingVals(double low, double high, double exp)
{
    dynamic_cast<Oscillator*>(synthItem)->set_freq_scale_vals(low, high, exp);
}


