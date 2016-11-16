#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <QVector>
#include <QDebug>
#include <QAtomicInteger>

#include "atomic"

namespace son
{

class RingBuffer
{
public:
    RingBuffer(int size);

    void reset();

    bool push(const QVector<double>* item);
    const QVector<double>* pop();

    bool empty() const;
    bool full() const;

private:

    QAtomicInteger<unsigned int> currentSize;
    QAtomicInteger<unsigned int> capacity;
    QAtomicInteger<unsigned int> head;
    QAtomicInteger<unsigned int> tail;

    QVector<const QVector<double>*> array;

};

}

#endif // RINGBUFFER_H


