#include "sequencer.h"


namespace son {

Sequencer::Sequencer()
{

}

bool Sequencer::enqueue(QVector<double> data)
{
    bool result = ringBuffer->push(data);
    return result;
}

bool Sequencer::enqueue(QVector<double> data, unsigned int delta)
{

}

void Sequencer::setRingBuffer(son::RingBuffer *buffer)
{
    ringBuffer = buffer;
}

void Sequencer::tick()
{

}

}
