#ifndef SMAFILTER_H
#define SMAFILTER_H

#include <QObject>
#include "ringbuffer.h"

namespace sow {

class SmaFilter : public QObject
{
    Q_OBJECT
public:
    explicit SmaFilter(QObject *parent = nullptr);
    float sma(float value);
    uint n() const;
    void setN(float n);
    void flush();

private:

    RingBuffer<float>* buffer_;
    bool initialized_ = false;
    uint n_ = 2;

signals:

};

} // Namespace sow.

#endif // SMAFILTER_H
