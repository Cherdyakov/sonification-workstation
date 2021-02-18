#include "dataprocessorcontroller.h"

namespace sow {

DataProcessorController::DataProcessorController(QObject *parent, Dataset* dataset) : QObject(parent)
{
    dataset_ = dataset;
}

std::vector<float> DataProcessorController::getData(uint row)
{
    std::vector<float> dataRow;
//    for (uint i = 0; i < processors_.size(); i++)
//    {
//        dataRow.push_back(processors_[i]->getValue(row));
//    }
    return dataRow;
}

void DataProcessorController::onDatasetChanged(Dataset *dataset)
{
//    processors_.resize(dataset->rows());
}

void DataProcessorController::onProcessingTypeChanged(uint track, ENUMS::PROCESSING_TYPE type)
{
//    processors_[track]->setProcessingType(type);
}

void DataProcessorController::onAlphaChanged(uint track, float alpha)
{
//    processors_[track]->setAlpha(alpha);
}

void DataProcessorController::onNvalChanged(uint track, uint n)
{
//    processors_[track]->setN(n);
}

} // Namespace sow.
