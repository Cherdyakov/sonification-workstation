#ifndef DATAPROCESSOR_H
#define DATAPROCESSOR_H

#include <QObject>
#include "enums.h"
#include "dataset.h"
#include "ringbuffer.h"
#include "emafilter.h"
#include "smafilter.h"

namespace sow {

class DataProcessor : public QObject
{
    Q_OBJECT
public:
    explicit DataProcessor(QObject *parent = nullptr, Dataset* dataset = nullptr);

    // Get the next value
    float getValue(uint row, uint col);

    ENUMS::PROCESSING_TYPE processingType();
    void setProcessingType(ENUMS::PROCESSING_TYPE type);
    uint n() const;
    void setN(float n);
    void flush();
    void step();

private:

    Dataset* dataset_;
    EmaFilter emaFilter_;
    SmaFilter smaFilter_;

    ENUMS::PROCESSING_TYPE processingType_ = ENUMS::PROCESSING_TYPE::NONE;
    uint rowPrevious_ = 0;
    uint n_;
    bool initialized_ = false;
    bool step_ = true;

signals:

public slots:



};

} // Namespace sow.

#endif // DATAPROCESSOR_H
