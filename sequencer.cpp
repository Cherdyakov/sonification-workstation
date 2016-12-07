#include "sequencer.h"


namespace son {

Sequencer::Sequencer()
{
    paused = true;
    counter = 0;
    setSpeed(1);
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

void Sequencer::setPaused(bool pause)
{
    if(paused != pause)
    {
        paused = pause;
    }
}

void Sequencer::tick()
{
    if(paused) {
        return;
    }
    counter++;
    if(counter > ticksPerStep) {
        step();
        counter = 0;
    }
}

void Sequencer::step()
{
    emit(stepped());
}

void Sequencer::setSpeed(int stepsPerSec)
{
    ticksPerStep = 44100 / stepsPerSec;
}

}
