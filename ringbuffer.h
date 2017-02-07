#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <atomic>
#include <vector>

namespace son
{
class RingBuffer;
}

class son::RingBuffer
{
public:
    RingBuffer(int cap = 2048, int ch = 0);

    void reset();

    bool push(std::vector<double> dataItem);
    bool pop(std::vector<double> *dataItem);

    bool empty() const;
    bool full() const;

private:

    std::atomic<int> currentSize;
    std::atomic<int> capacity;
    std::atomic<int> channels;
    std::atomic<int> head;
    std::atomic<int> tail;

    std::vector<double> array;

};

#endif // RINGBUFFER_H


