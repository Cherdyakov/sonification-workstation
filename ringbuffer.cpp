#include "ringbuffer.h"

namespace son
{

RingBuffer::RingBuffer(int size)
{ 

    head = 0;
    tail = 0;
    currentSize = 0;
    capacity = size;
    array.resize(size);

}

void RingBuffer::reset()
{
    currentSize = 0;
    head = 0;
    tail = 0;
    head = 0;
}

bool RingBuffer::push(const QVector<double>* item)
{

    //buffer size at max
    if(full())
    {
        return false;
    }
    if(head > array.count() - 1)
    {
        head = 0;
    }
    array[head] = item;
    head++;
    currentSize++;
    return true;
}

const QVector<double>* RingBuffer::pop()
{
    //bounds check
    if(tail > array.count() - 1)
    {
        tail = 0;
    }
    //tail has reached head
    if(empty())
    {
        return NULL;
    }
    //tail behind head, data avail
    const QVector<double>* data = array[tail];
    tail++;
    currentSize--;
    return data;
}

bool RingBuffer::empty() const
{
    return(tail == head);
}

bool RingBuffer::full() const
{
    return(currentSize == capacity);
}

}
