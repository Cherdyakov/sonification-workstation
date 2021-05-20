#include "dataprocessorcontroller.h"
#include <QDebug>

namespace sow {

DataProcessorController::DataProcessorController(QObject *parent, Dataset* dataset) : QObject(parent)
{
    dataset_ = dataset;
}

std::vector<float> DataProcessorController::getData(uint row, float mu)
{
    uint nextRow = row + 1 > dataset_->rows() ? 0 : row + 1;
    for (uint i = 0; i < processors_.size(); i++)
    {
        rowData[i] = processors_[i]->getValue(row, i);
        nextRowData[i] = nextValueProcessors_[i]->getValue(nextRow, i);
    }

    std::vector<float> returnData =  rowData;

    for (uint i = 0; i < interpolateFlags_.size(); i++)
    {
        if(interpolateFlags_[i]) {
            returnData[i] = interpolateValue(rowData[i], nextRowData[i], mu);
        }
    }

    return returnData;
}

void DataProcessorController::step()
{
    qDebug() << "Current C: " << rowData[2] << ", Next C: " << nextRowData[2];
}

void DataProcessorController::controlProcess()
{
    DataProcessorControllerCommand cmd;
    while(dataProcessorControllerCommandBuffer_.pop(&cmd))
    {
        processDataProcessorControllerCommand(cmd);
    }
}

bool DataProcessorController::interpolate()
{
    for(uint i = 0; i < interpolateFlags_.size(); i++)
    {
        if(interpolateFlags_[i]) return true;
    }
    return false;
}

void DataProcessorController::processDataProcessorControllerCommand(DataProcessorControllerCommand cmd)
{
    cmd.track -= 1;
    switch (cmd.type) {
    case ENUMS::DATA_PROCESSOR_CMD::FLUSH:
        flush();
        break;
    case ENUMS::DATA_PROCESSOR_CMD::PROC_TYPE:
        processors_[cmd.track]->setProcessingType(cmd.procType);
        nextValueProcessors_[cmd.track]->setProcessingType(cmd.procType);
        break;
    case ENUMS::DATA_PROCESSOR_CMD::INTERPOLATE:
        interpolateFlags_[cmd.track] = (cmd.value == 0.0f) ? false : true;
        break;
    case ENUMS::DATA_PROCESSOR_CMD::N_VAL:
        processors_[cmd.track]->setN(static_cast<int>(cmd.value));
        nextValueProcessors_[cmd.track]->setN(static_cast<int>(cmd.value));
        break;
    }
}

void DataProcessorController::resize(uint size)
{
    processors_.clear();
    nextValueProcessors_.clear();
    interpolateFlags_.clear();
    for (uint i = 0; i < size; i++)
    {
        DataProcessor* p = new DataProcessor(this, dataset_);
        DataProcessor* np = new DataProcessor(this, dataset_);
        processors_.push_back(p);
        nextValueProcessors_.push_back(np);
    }
    interpolateFlags_.resize(size);
    rowData.resize(size);
    nextRowData.resize(size);
}

void DataProcessorController::flush()
{
    for (uint i = 0; i < processors_.size(); i ++)
    {
        processors_[i]->flush();
        nextValueProcessors_[i]->flush();
    }
}

void DataProcessorController::onDatasetChanged(Dataset *dataset)
{
    if(dataset_ != dataset)
    {
        dataset_ = dataset;
    }
    resize(dataset_->cols());
}

void DataProcessorController::onProcessingTypeChanged(uint track, ENUMS::PROCESSING_TYPE type)
{
    DataProcessorControllerCommand cmd;
    cmd.type = ENUMS::DATA_PROCESSOR_CMD::PROC_TYPE;
    cmd.track = track;
    cmd.procType = type;
    dataProcessorControllerCommandBuffer_.push(cmd);
}

void DataProcessorController::onNvalChanged(uint track, uint n)
{
    DataProcessorControllerCommand cmd;
    cmd.type = ENUMS::DATA_PROCESSOR_CMD::N_VAL;
    cmd.track = track;
    cmd.value = n;
    dataProcessorControllerCommandBuffer_.push(cmd);
}

float DataProcessorController::interpolateValue(const float first, const float second, const float mu)
{
    float value = ((1 - mu) * first) + (mu * second);
    return value;
}

void DataProcessorController::onInterpolateChanged(uint track, bool interpolate)
{

    DataProcessorControllerCommand cmd;
    cmd.type = ENUMS::DATA_PROCESSOR_CMD::INTERPOLATE;
    cmd.track = track;
    cmd.value = interpolate ? 1.0f : 0.0f;
    dataProcessorControllerCommandBuffer_.push(cmd);
}

void DataProcessorController::onPauseChanged()
{
//    flush();
}

} // Namespace sow.
