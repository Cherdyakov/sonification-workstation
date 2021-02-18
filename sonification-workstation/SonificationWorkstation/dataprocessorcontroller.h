#ifndef DATAPROCESSORCONTROLLER_H
#define DATAPROCESSORCONTROLLER_H

#include <QObject>
#include "dataprocessor.h"
#include "dataset.h"

namespace sow {

class DataProcessorController : public QObject
{
    Q_OBJECT
public:
    explicit DataProcessorController(QObject *parent = nullptr, Dataset* dataset = nullptr);

    std::vector<float> getData(uint row);

private:

    std::vector<DataProcessor>* processors_;
    Dataset* dataset_;

signals:

public slots:

    void onDatasetChanged(Dataset* dataset);
    // slots for data processing settings
    void onProcessingTypeChanged(uint track, ENUMS::PROCESSING_TYPE type);
    void onAlphaChanged(uint track, float alpha);
    void onNvalChanged(uint track, uint n);

};

} // Namespace sow.

#endif // DATAPROCESSORCONTROLLER_H
