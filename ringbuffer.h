#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <atomic>
#include "synthcommand.h"

namespace son
{

class RingBuffer
{
public:
    RingBuffer(int cap = 512);

    void reset();

    bool push(SynthCommand* command);
    bool pop(SynthCommand* command);

    bool empty() const;
    bool full() const;

private:

    std::atomic<int> currentSize;
    std::atomic<int> capacity;
    std::atomic<int> head;
    std::atomic<int> tail;
    std::vector<SynthCommand> array;

};

} //namespace son

#endif // RINGBUFFER_H


