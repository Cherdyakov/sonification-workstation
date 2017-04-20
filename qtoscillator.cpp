#include "qtoscillator.h"

using namespace son;

QtOscillator::QtOscillator(SynthItem *item, QObject *parent) : QtSynthItem(parent)
{
    synthItem = item;
    oscillator = dynamic_cast<Oscillator*>(synthItem);
}

void QtOscillator::setWaveform(WAVEFORM waveform)
{
    oscillator->setWaveform((SynthItem::WAVEFORM)waveform);
}

void QtOscillator::setFixedFreq(double freq)
{
    oscillator->setFixedFreq(freq);
}

void QtOscillator::setUseFixedFreq(bool fixed)
{
    oscillator->setUseFixedFreq(fixed);
}

void QtOscillator::setUseFreqScaling(bool scaling)
{
    oscillator->setUseFreqScaling(scaling);
}

void QtOscillator::setFreqScalingVals(double low, double high, double exp)
{
    oscillator->setFreqScalingVals(low, high, exp);
}
