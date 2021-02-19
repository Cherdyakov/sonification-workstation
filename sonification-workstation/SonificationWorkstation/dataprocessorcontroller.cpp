#include "dataprocessorcontroller.h"

namespace sow {

DataProcessorController::DataProcessorController(QObject *parent, Dataset* dataset) : QObject(parent)
{
    dataset_ = dataset;
}

std::vector<float> DataProcessorController::getData(uint row)
{
    std::vector<float> dataRow;
    for (uint i = 0; i < processors_.size(); i++)
    {
        dataRow.push_back(processors_[i]->getValue(row, i));
    }
    return dataRow;
}

void DataProcessorController::controlProcess()
{
    DataProcessorControllerCommand cmd;
    while(dataProcessorControllerCommandBuffer_.pop(&cmd))
    {
        processDataProcessorControllerCommand(cmd);
    }
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
        break;
    case ENUMS::DATA_PROCESSOR_CMD::INTERPOLATE:
//        processors_[cmd.track]->setProcessingType(type);
        break;
    case ENUMS::DATA_PROCESSOR_CMD::ALPHA:
        processors_[cmd.track]->setAlpha(cmd.value);
        break;
    case ENUMS::DATA_PROCESSOR_CMD::N_VAL:
        processors_[cmd.track]->setN(static_cast<int>(cmd.value));
        break;
    }
}

void DataProcessorController::resize(uint size)
{
    processors_.clear();
    for (uint i = 0; i < size; i++)
    {
        DataProcessor* p = new DataProcessor(this, dataset_, 2);
        processors_.push_back(p);
    }
}

void DataProcessorController::flush()
{
    for (int i = 0; i < processors_.size(); i ++)
    {
        processors_[i]->flush();
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

void DataProcessorController::onAlphaChanged(uint track, float alpha)
{
    DataProcessorControllerCommand cmd;
    cmd.type = ENUMS::DATA_PROCESSOR_CMD::ALPHA;
    cmd.track = track;
    cmd.value = alpha;
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

void DataProcessorController::onPauseChanged()
{
    flush();
}

} // Namespace sow.
