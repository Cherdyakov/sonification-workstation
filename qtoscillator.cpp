#include "qtoscillator.h"

using namespace son;

QtOscillator::QtOscillator(SynthItem *item, QObject *parent) : QtSynthItem(parent)
{
    synthItem = item;
}

void QtOscillator::addChild(QtSynthItem *child, CHILD_TYPE type)
{
    Oscillator* osc = static_cast<Oscillator*>(synthItem);
    osc->addChild(child->implementation(), (SynthItem::SON_CHILD_TYPE)type);
}

void QtOscillator::removeChild(QtSynthItem *child)
{
    Oscillator* osc = static_cast<Oscillator*>(synthItem);
    osc->removeChild(child->implementation());
}

void QtOscillator::setDataItem(std::vector<double> *data)
{
    Oscillator* osc = static_cast<Oscillator*>(synthItem);
    osc->setDataItem(data);
}

void QtOscillator::setWaveform(WAVEFORM waveform)
{
    Oscillator* osc = static_cast<Oscillator*>(synthItem);
    osc->setWaveform((SynthItem::SON_WAVEFORM)waveform);
}

void QtOscillator::setFreq(double freq)
{
    Oscillator* osc = static_cast<Oscillator*>(synthItem);
    osc->setFreq(freq);
}

void QtOscillator::setFixedFreqs(bool fixed)
{
    Oscillator* osc = static_cast<Oscillator*>(synthItem);
    osc->setFixedFreqs(fixed);
}

void QtOscillator::setIndexes(QVector<int> indexes)
{
    std::vector<int> vec = indexes.toStdVector();
    Oscillator* osc = static_cast<Oscillator*>(synthItem);
    osc->setIndexes(vec);
}
