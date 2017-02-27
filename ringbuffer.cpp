#include "ringbuffer.h"

namespace son {

RingBuffer::RingBuffer(int cap)
{ 
    head = 0;
    tail = 0;
    currentSize = 0;
    capacity = cap;
    array.resize(capacity);
}

void RingBuffer::reset()
{
    head = 0;
    tail = 0;
    currentSize = 0;
}

bool RingBuffer::push(SynthCommand* command)
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

    array[head] = *command;

    head++;
    currentSize++;
    return true;
}

bool RingBuffer::pop(SynthCommand* command)
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

    *command = array[tail];

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
