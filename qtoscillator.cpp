#include "qtoscillator.h"

using namespace son;

QtOscillator::QtOscillator(QObject *parent) : QObject(parent)
{

}

void QtOscillator::addChild(SynthItem *child, SynthItem::SON_CHILD_TYPE type)
{
    oscillator.addChild(child, type);
}

void QtOscillator::removeChild(SynthItem *child)
{
    oscillator.removeChild(child);
}

void QtOscillator::setDataItem(std::vector<double> *data)
{
    oscillator.setDataItem(data);
}

void QtOscillator::setWaveform(SynthItem::SON_WAVEFORM waveform)
{
    oscillator.setWaveform(waveform);
}

void QtOscillator::setFreq(double freq)
{
    oscillator.setFreq(freq);
}

void QtOscillator::setFixedFreqs(bool fixed)
{
    oscillator.setFixedFreqs(fixed);
}

void QtOscillator::setIndexes(std::vector<int> indexes)
{
    oscillator.setIndexes(indexes);
}
