#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <QVector>
#include <QDebug>
#include <QAtomicInteger>

namespace son
{
class RingBuffer;
}

class son::RingBuffer
{
public:
    RingBuffer(int size = 100);

    void reset();

    bool push(QVector<double> item);
    QVector<double> pop();

    bool empty() const;
    bool full() const;

private:

    QAtomicInteger<unsigned int> currentSize;
    QAtomicInteger<unsigned int> capacity;
    QAtomicInteger<unsigned int> head;
    QAtomicInteger<unsigned int> tail;

    QVector<QVector<double>>* array;

};

#endif // RINGBUFFER_H


