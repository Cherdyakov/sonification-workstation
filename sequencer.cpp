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

void Sequencer::start()
{
    ringBuffer->reset();
    step();
    paused = false;
}

void Sequencer::stop()
{
    paused = true;
}

void Sequencer::setSpeed(int stepsPerSec)
{
    ticksPerStep = 44100 / stepsPerSec;
}

}
