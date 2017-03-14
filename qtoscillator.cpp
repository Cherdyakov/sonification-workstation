#include "qtoscillator.h"

using namespace son;

QtOscillator::QtOscillator(SynthItem *item, QObject *parent) : QtSynthItem(parent)
{
    synthItem = item;

}

void QtOscillator::addChild(QtSynthItem *child, CHILD_TYPE type)
{
    Oscillator* oscillator =  dynamic_cast<Oscillator*>(synthItem);
    oscillator->addChild(child->implementation(), (SynthItem::SON_CHILD_TYPE)type);
}

void QtOscillator::removeChild(QtSynthItem *child)
{
    Oscillator* oscillator =  dynamic_cast<Oscillator*>(synthItem);
    oscillator->removeChild(child->implementation());
}

void QtOscillator::setWaveform(WAVEFORM waveform)
{
    Oscillator* oscillator =  dynamic_cast<Oscillator*>(synthItem);
    oscillator->setWaveform((SynthItem::SON_WAVEFORM)waveform);
}

void QtOscillator::setFreq(double freq)
{
    Oscillator* oscillator =  dynamic_cast<Oscillator*>(synthItem);
    oscillator->setFreq(freq);
}

void QtOscillator::setFixedFreqs(bool fixed)
{
    Oscillator* oscillator =  dynamic_cast<Oscillator*>(synthItem);
    oscillator->setFixedFreqs(fixed);
}

void QtOscillator::setIndexes(QVector<int> indexes)
{
    std::vector<int> vec = indexes.toStdVector();
    Oscillator* oscillator =  dynamic_cast<Oscillator*>(synthItem);
    oscillator->setIndexes(vec);
}
