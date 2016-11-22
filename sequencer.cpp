#include "sequencer.h"


namespace son {

Sequencer::Sequencer()
{
    paused = true;
    timer = new QTimer(this);
    setSpeed(1.0);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(step()));
    timer->start();
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

void Sequencer::setSpeed(double s)
{
    double speed = 1000.0 / s;
    timer->setInterval(speed);
}

void Sequencer::step()
{
    if(paused)
    {
        return;
    }
    emit stepped();

}

}
