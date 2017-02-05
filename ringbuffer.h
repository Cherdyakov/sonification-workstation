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
    RingBuffer(int size = 2048);

    void reset();

    bool push(QVector<double> item);
    bool pop(QVector<double>* item);

    bool empty() const;
    bool full() const;

private:

    QAtomicInteger<int> currentSize;
    QAtomicInteger<int> capacity;
    QAtomicInteger<int> head;
    QAtomicInteger<int> tail;

    QVector<QVector<double>>* array;

};

#endif // RINGBUFFER_H


