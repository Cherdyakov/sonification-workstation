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

    std::vector<ENUMS::PROCESSING_TYPE> procTypes_;
    std::vector<float> alphas_;
    std::vector<int> nVals_;
    Dataset* dataset_;

    float getSimpleAverageValue(unsigned int row, unsigned int col, int n);
    float getExponentialAverageValue(int row, int col, int n, float alpha);
    std::vector<float> getSimpleAverageData(int idx);
    std::vector<float> getExponentialAverageData(int idx);


signals:

public slots:

    // slots for data processing settings
    void onProcessingTypeChanged(std::vector<ENUMS::PROCESSING_TYPE> procTypes);
    void onAlphaChanged(std::vector<float> alphas);
    void onNvalChanged( std::vector<int> nVals);

};

} // Namespace sow.

#endif // DATAPROCESSOR_H
