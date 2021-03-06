#ifndef RingBuffer_H
#define RingBuffer_H

#include <QAtomicInt>

namespace sow
{

template <class T>
class RingBuffer
{
public:
    RingBuffer(int cap = 512);
    ~RingBuffer();

    void reset();
    void resize(const uint size);
    uint size();

    bool push(T item);
    bool pop(T* item);
    bool pop();
    bool at(T* item, const uint idx) const;

    bool empty() const;
    bool full() const;

private:

    QAtomicInt maxCapacity;
    QAtomicInt currentSize;
    QAtomicInt capacity;
    QAtomicInt head;
    QAtomicInt tail;
    T* array;

};

// Function implementations
template <class T>
RingBuffer<T>::RingBuffer(int cap)
{
    head = 0;
    tail = 0;
    currentSize = 0;
    capacity = maxCapacity = cap;
    array = new T[capacity];
}

template<class T>
RingBuffer<T>::~RingBuffer()
{
    delete[] array;
}

template<class T>
void RingBuffer<T>::reset()
{
    head = 0;
    tail = 0;
    currentSize = 0;
}

template<class T>
void RingBuffer<T>::resize(uint size)
{
    reset();
    if (size > maxCapacity)
    {
        size = maxCapacity;
    }
    capacity = size;
}

template<class T>
uint RingBuffer<T>::size()
{
    return currentSize;
}

template<class T>
bool RingBuffer<T>::push(T item)
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

    array[head] = item;

    head++;
    currentSize++;
    return true;
}

template<class T>
bool RingBuffer<T>::pop(T* item)
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

    *item = array[tail];

    tail++;
    currentSize--;
    return true;
}

template<class T>
bool RingBuffer<T>::pop()
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

    tail++;
    currentSize--;
    return true;
}

// ACCESSES RAW ARRAY CONTENTS
template<class T>
bool RingBuffer<T>::at(T* item, const uint idx) const
{
    // invalid index
    if(idx > currentSize)
    {
        return false;
    }
    // tail has caught up to head
    if(empty())
    {
        return false;
    }
    *item = array[idx];
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

} //namespace sow

#endif // RingBuffer_H


