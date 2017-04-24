#include "qtoscillator.h"

using namespace son;

QtOscillator::QtOscillator(SynthItem *item, QObject *parent) : QtSynthItem(parent)
{
    synthItem = item;
}

void QtOscillator::setWaveform(WAVEFORM waveform)
{
    dynamic_cast<Oscillator*>(synthItem)->setWaveform((SynthItem::WAVEFORM)waveform);
}

void QtOscillator::setFixedFreq(double freq)
{
   dynamic_cast<Oscillator*>(synthItem)->setFixedFreq(freq);
}

void QtOscillator::setUseFixedFreq(bool fixed)
{
   dynamic_cast<Oscillator*>(synthItem)->setUseFixedFreq(fixed);
}

void QtOscillator::setUseFreqScaling(bool scaling)
{
   dynamic_cast<Oscillator*>(synthItem)->setUseFreqScaling(scaling);
}

void QtOscillator::setFreqScalingVals(double low, double high, double exp)
{
    dynamic_cast<Oscillator*>(synthItem)->setFreqScalingVals(low, high, exp);
}


