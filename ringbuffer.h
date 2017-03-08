#ifndef RingBuffer_H
#define RingBuffer_H

#include <atomic>
#include "synthcommand.h"


namespace son
{

template <class T>
class RingBuffer
{
public:
    RingBuffer(int cap = 512);

    void reset();

    bool push(T command);
    bool pop(T* command);

    bool empty() const;
    bool full() const;

private:

    std::atomic<int> currentSize;
    std::atomic<int> capacity;
    std::atomic<int> head;
    std::atomic<int> tail;
    std::vector<SynthCommand> array;

};

// Function implementations
template <class T>
RingBuffer<T>::RingBuffer(int cap)
{
    head = 0;
    tail = 0;
    currentSize = 0;
    capacity = cap;
    array.resize(capacity);
}

template<class T>
void RingBuffer<T>::reset()
{
    head = 0;
    tail = 0;
    currentSize = 0;
}

template<class T>
bool RingBuffer<T>::push(T command)
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

    array[head] = command;

    head++;
    currentSize++;
    return true;
}

template<class T>
bool RingBuffer<T>::pop(T* command)
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

template<class T>
bool RingBuffer<T>::empty() const
{
    return(currentSize == 0);
}

template<class T>
bool RingBuffer<T>::full() const
{
    return(currentSize == capacity);
}

} //namespace son

#endif // RingBuffer_H


