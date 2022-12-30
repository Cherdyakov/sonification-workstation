#ifndef RingBuffer_H
#define RingBuffer_H

#include <QAtomicInt>
#include <stdexcept>

namespace sow
{

template <class T>
class RingBuffer
{
public:
    RingBuffer(int max = 512);
    ~RingBuffer();

    void reset();
    void resize(uint n);
    size_t size();

    void push(T item);
    bool pop(T* item);
    bool pop();
    bool at(T* item, const size_t idx) const;

    bool empty() const;
    bool full() const;

private:

    QAtomicInt max_;
    QAtomicInt capacity_;
    QAtomicInt head_;
    QAtomicInt tail_;
    bool full_;
    T* array_;

};

// Function implementations
template <class T>
RingBuffer<T>::RingBuffer(int max)
{
    if(max < 1) throw std::invalid_argument("Buffer max size cannot be less than 1");
    head_ = 0;
    tail_ = 0;
    max_ = max;
    capacity_ = max_;
    array_ = new T[max_];
}

template<class T>
RingBuffer<T>::~RingBuffer()
{
    delete[] array_;
}

template<class T>
void RingBuffer<T>::reset()
{
    head_ = tail_ = 0;
    full_ = false;
}

template<class T>
void RingBuffer<T>::resize(uint n)
{
    if((n < 1) || (n > max_)) throw std::invalid_argument("Buffer size out of range");
    reset();
    if (n > max_) n = max_;
    capacity_ = n;
}

template<class T>
size_t RingBuffer<T>::size()
{
    size_t size = capacity_;
    if(!full_)
    {
        if(head_ >= tail_)
        {
            size = head_ - tail_;
        }
        else
        {
            size = capacity_ + head_ - tail_;
        }
    }
    return size;
}

template<class T>
void RingBuffer<T>::push(T item)
{
    array_[head_] = item;

    if(full_)
    {
        if(++tail_ > (capacity_ - 1))
        {
            tail_ -= capacity_;
        }
    }

    if(++head_ > (capacity_ - 1))
    {
        head_ -= capacity_;
    }

    full_ = head_ == tail_;
}

template<class T>
bool RingBuffer<T>::pop(T* item)
{
    //tail has caught up to head
    if(empty())
    {
        return false;
    }

    *item = array_[tail_];
    full_ = false;
    if(++tail_ >= capacity_)
    {
        tail_ -= capacity_;
    }

    return true;
}

template<class T>
bool RingBuffer<T>::pop()
{
    //tail has caught up to head
    if(empty())
    {
        return false;
    }

    //bounds check
    if(++tail_ >= capacity_)
    {
        tail_ -= capacity_;
    }

    return true;
}

// DIRECT ACCESS TO BUFFER CONTENTS
template<class T>
bool RingBuffer<T>::at(T* item, const size_t idx) const
{
    // tail has caught up to head
    if(empty())
    {
        return false;
    }

    size_t verifiedIdx = tail_ + idx;
    if (verifiedIdx > (capacity_ - 1)) {
        verifiedIdx -= capacity_;
    }

    *item = array_[verifiedIdx];
    return true;
}

template<class T>
bool RingBuffer<T>::empty() const
{
    return(!full_ && (head_ == tail_));
}

template<class T>
bool RingBuffer<T>::full() const
{
    return full_;
}

} //namespace sow

#endif // RingBuffer_H


