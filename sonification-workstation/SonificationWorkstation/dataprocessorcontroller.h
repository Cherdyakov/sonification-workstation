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

    std::vector<float> getData(uint row, float mu); // called every new data value (step)
    void controlProcess(); // called every process block
    bool interpolate();

private:

    RingBuffer<DataProcessorControllerCommand> dataProcessorControllerCommandBuffer_;
    std::vector<DataProcessor*> processors_;
    Dataset* dataset_;

    void processDataProcessorControllerCommand(DataProcessorControllerCommand cmd);
    void resize(uint size);
    void flush();

signals:

public slots:

    void onDatasetChanged(Dataset* dataset);
    // slots for data processing settings
    void onProcessingTypeChanged(uint track, ENUMS::PROCESSING_TYPE type);
    void onNvalChanged(uint track, uint n);
    void onInterpolateChanged(uint track, bool interpolate);
    void onPauseChanged();

};

} // Namespace sow.

#endif // DATAPROCESSORCONTROLLER_H
