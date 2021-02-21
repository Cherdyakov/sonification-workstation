#ifndef DATAPROCESSOR_H
#define DATAPROCESSOR_H

#include <QObject>
#include "enums.h"
#include "dataset.h"
#include "ringbuffer.h"

namespace sow {

class DataProcessor : public QObject
{
    Q_OBJECT
public:
    explicit DataProcessor(QObject *parent = nullptr, Dataset* dataset = nullptr, uint size = 512);

    // Get the next value
    float getValue(uint row, uint col, float mu);

    ENUMS::PROCESSING_TYPE processingType();
    void setProcessingType(ENUMS::PROCESSING_TYPE type);
    uint n() const;
    void setN(float n);
    void flush();
    bool interpolate();
    void setInterpolate(bool interpolate);

private:

    Dataset* dataset_;
    RingBuffer<float>* buffer_;
    ENUMS::PROCESSING_TYPE processingType_ = ENUMS::PROCESSING_TYPE::NONE;
    uint n_ = 2;
    float emaPrevious_;
    float valuePrevious_;
    bool initialized_ = false;
    bool interpolate_ = false;
    float sma(unsigned int row, unsigned int col);
    float ema(int row, int col);
    float interpolate(float first, float second, float mu);

signals:

public slots:



};

} // Namespace sow.

#endif // DATAPROCESSOR_H
