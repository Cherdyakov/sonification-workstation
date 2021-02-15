#ifndef DATAPROCESSOR_H
#define DATAPROCESSOR_H

#include <QObject>
#include "enums.h"
#include "dataset.h"

namespace sow {

class DataProcessor : public QObject
{
    Q_OBJECT
public:
    explicit DataProcessor(QObject *parent = nullptr, Dataset* dataset = nullptr);

    // Get the next set of data values
    std::vector<float> getData(uint idx);

private:

    ENUMS::PROCESSING_TYPE procType_;
    float alpha_;
    int n_;
    Dataset* dataset_;

    std::vector<float> getSimpleAverageData(int idx);
    std::vector<float> getExponentialAverageData(int idx);

    std::vector<std::vector<float>> getMultipleRows(int idx, int n);

signals:

public slots:

    // slots for data processing settings
    void onProcessingTypeChanged(ENUMS::PROCESSING_TYPE procType);
    void onAlphaChanged(int alpha);

};

} // Namespace sow.

#endif // DATAPROCESSOR_H
