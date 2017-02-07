#include "ringbuffer.h"

namespace son {

RingBuffer::RingBuffer(int cap, int ch)
{ 
    head = 0;
    tail = 0;
    currentSize = 0;
    capacity = cap;
    channels = ch;
    array.resize(capacity * channels);
}

void RingBuffer::reset()
{
    head = 0;
    tail = 0;
    currentSize = 0;
}

bool RingBuffer::push(std::vector<double> dataItem)
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

    for(int i = 0; i < channels; i++)
    {
        array[(head * channels) + i] = dataItem[i];
    }

    head++;
    currentSize++;
    return true;
}

bool RingBuffer::pop(std::vector<double> *dataItem)
{
    //bounds check
    if(tail > capacity - 1)
    {
        tail = 0;
    }
    //tail has caught up to head
    if(empty())
    {
        return false;
    }

    for(int i = 0; i < channels; i++)
    {
        (*dataItem)[i] = array[(tail * channels) + i];
    }

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

}
