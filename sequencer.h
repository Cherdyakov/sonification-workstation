#ifndef SEQUENCER_H
#define SEQUENCER_H

#include <QVector>
#include <QDebug>

#include "ringbuffer.h"

namespace son
{

class Sequencer
{
public:
    Sequencer();

    bool enqueue(QVector<double> data);
    bool enqueue(QVector<double> data, unsigned int delta);
    void setRingBuffer(RingBuffer* buffer);
    //every sample, for keeping time
    void tick();


private:
    double speed;
    RingBuffer* ringBuffer;



};

} // son namespace

#endif // SEQUENCER_H
