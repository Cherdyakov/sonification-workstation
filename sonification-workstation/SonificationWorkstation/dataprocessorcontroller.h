#ifndef DATAPROCESSORCONTROLLER_H
#define DATAPROCESSORCONTROLLER_H

#include <QObject>
#include "dataprocessor.h"
#include "dataset.h"
#include "commands.h"

namespace sow {

class DataProcessorController : public QObject
{
    Q_OBJECT
public:
    explicit DataProcessorController(QObject *parent = nullptr, Dataset* dataset = nullptr);

    std::vector<float> getData(uint row); // called every new data value (step)
    void controlProcess(); // called every process block

private:

    RingBuffer<DataProcessorControllerCommand> dataProcessorControllerCommandBuffer_;
    std::vector<DataProcessor*> processors_;
    Dataset* dataset_;

    void processDataProcessorControllerCommand(DataProcessorControllerCommand cmd);
    void resize(uint size);

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
