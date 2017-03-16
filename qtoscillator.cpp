#include "qtoscillator.h"

using namespace son;

QtOscillator::QtOscillator(SynthItem *item, QObject *parent) : QtSynthItem(parent)
{
    synthItem = item;
    oscillator = dynamic_cast<Oscillator*>(synthItem);
}

void QtOscillator::setWaveform(WAVEFORM waveform)
{
    oscillator->setWaveform((SynthItem::SON_WAVEFORM)waveform);
}

void QtOscillator::setFreq(double freq)
{
    oscillator->setFreq(freq);
}

void QtOscillator::setFixedFreqs(bool fixed)
{
    oscillator->setFixedFreqs(fixed);
}
