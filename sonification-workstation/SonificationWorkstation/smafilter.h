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
    virtual float value(float in) override;
    virtual void setN(int n) override;

private:

    RingBuffer<float>* buffer_;

signals:

};

} // Namespace sow.

#endif // SMAFILTER_H
