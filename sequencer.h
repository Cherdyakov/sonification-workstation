#ifndef SEQUENCER_H
#define SEQUENCER_H

#include <QObject>
#include <QTimer>
#include <QVector>
#include <QDebug>

#include "ringbuffer.h"

namespace son
{

class Sequencer : public QObject
{
    Q_OBJECT

public:
    Sequencer();

    bool enqueue(QVector<double> data);
    bool enqueue(QVector<double> data, unsigned int delta);
    void setRingBuffer(RingBuffer* buffer);

    void setPaused(bool pause);
    void setStepSize(int step);
    void setSpeed(int speed);
    void tick();


private:

    RingBuffer* ringBuffer;

    std::atomic<bool> paused;
    std::atomic<int> stepsPerSecond;
    int ticksPerStep;
    int counter;
    void step();

private slots:


signals:

    void stepped();


};

} // son namespace

#endif // SEQUENCER_H
