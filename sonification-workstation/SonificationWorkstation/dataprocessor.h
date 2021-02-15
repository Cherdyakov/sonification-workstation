#ifndef DATAPROCESSOR_H
#define DATAPROCESSOR_H

#include <QObject>
#include "dataset.h"
#include "enums.h"

namespace sow {

class DataProcessor : public QObject
{
    Q_OBJECT
public:
    explicit DataProcessor(QObject *parent = nullptr);

    // Get the next set of data values
    std::vector<float> getData(uint idx);

private:

    ENUMS::PROCESSING_TYPE procType_;
    int alpha_;
    Dataset* dataset_;

    std::vector<float> getSimpleAverageData();
    std::vector<float> getExponentialAverageData();

signals:

public slots:

    // slots for data processing settings
    void onProcessingTypeChanged(ENUMS::PROCESSING_TYPE procType);
    void onAlphaChanged(int alpha);

};

} // Namespace sow.

#endif // DATAPROCESSOR_H
