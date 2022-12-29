#ifndef SMAFILTER_H
#define SMAFILTER_H

#include "filter.h"
#include "ringbuffer.h"

namespace sow {

class SmaFilter : public filter
{
    Q_OBJECT
public:
    explicit SmaFilter(QObject *parent = nullptr);
    virtual void push(float value) override;
    virtual float value() override;
    virtual void setN(uint n) override;
    virtual void flush() override;

private:

    RingBuffer<float>* buffer_;

signals:

};

} // Namespace sow.

#endif // SMAFILTER_H
