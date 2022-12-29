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
    void resize(const size_t size);
    size_t size();

    void push(T item);
    bool pop(T* item);
    bool pop();
    bool at(T* item, const size_t idx) const;

    bool empty() const;
    bool full() const;;

private:

    QAtomicInt max_;
    QAtomicInt size_;
    QAtomicInt head_;
    QAtomicInt tail_;
    bool full_;
    T* array_;

};

// Function implementations
template <class T>
RingBuffer<T>::RingBuffer(int cap)
{
    head_ = 0;
    tail_ = 0;
    size_ = 0;
    max_ = cap;
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
    head_ = tail_;
    full_ = false;
}

template<class T>
void RingBuffer<T>::resize(size_t size)
{
    reset();
    if (size > max_)
    {
        size = max_;
    }
    size_ = size;
}

template<class T>
size_t RingBuffer<T>::size()
{
    size_t size = max_;
    if(!full_)
    {
        if(head_ >= tail_)
        {
            size = head_ - tail_;
        }
        else
        {
            size = max_ + head_ - tail_;
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
        if(++tail_ > (max_ - 1))
        {
            tail_ -= max_;
        }
    }

    if(++head_ > (max_ - 1))
    {
        head_ -= max_;
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
    if(++tail_ >= max_)
    {
        tail_ -= max_;
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
    if(++tail_ >= max_)
    {
        tail_ -= max_;
    }

    return true;
}

// DIRECT ACCESS TO BUFFER CONTENTS
template<class T>
bool RingBuffer<T>::at(T* item, const size_t idx) const
{
    // invalid index
    if(idx > size_)
    {
        return false;
    }
    // tail has caught up to head
    if(empty())
    {
        return false;
    }

    size_t verifiedIdx = tail_ + idx;
    if (verifiedIdx > (max_ - 1)) {
        verifiedIdx -= max_;
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


