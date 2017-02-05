#include "ringbuffer.h"

using namespace son;

RingBuffer::RingBuffer(int size)
{ 
    head = 0;
    tail = 0;
    currentSize = 0;
    capacity = size;
    array = new QVector<QVector<double>>;
    array->resize(capacity);
}

void RingBuffer::reset()
{
    head = 0;
    tail = 0;
    currentSize = 0;
}

bool RingBuffer::push(QVector<double> item)
{
    //values written all the way to end
    if(head > capacity - 1)
    {
        head = 0;
    }

    //buffer size at max
    if(full())
    {
        return false;
    }

    array->replace(head, item);

    head++;
    currentSize++;
    return true;
}

bool RingBuffer::pop(QVector<double> *item)
{
    //bounds check
    if(tail > capacity - 1)
    {
        tail = 0;
    }
    //tail has reached head
    if(empty())
    {
        return false;
    }
    //tail behind head, data avail
    *item = array->at(tail);
    tail++;
    currentSize--;
    return true;
}

bool RingBuffer::empty() const
{
    return(currentSize == 0);
}

bool RingBuffer::full() const
{
    return(currentSize == capacity);
}
