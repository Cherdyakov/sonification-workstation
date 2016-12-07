#include "ringbuffer.h"

namespace son
{

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
    array->clear();
    array->resize(capacity);
}

bool RingBuffer::push(QVector<double> item)
{

    //buffer size at max
    if(full())
    {
        qDebug() << "ringbuffer: full!";
        return false;
    }
    if(head > array->count() - 1)
    {
        head = 0;
    }

    array->insert(head, item);
    head++;
    currentSize++;
    return true;
}

QVector<double> RingBuffer::pop()
{
    QVector<double> data;
    //bounds check
    if(tail > array->count() - 1)
    {
        tail = 0;
    }
    //tail has reached head
    if(empty())
    {
        return data;
    }
    //tail behind head, data avail
    data = array->at(tail);
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
