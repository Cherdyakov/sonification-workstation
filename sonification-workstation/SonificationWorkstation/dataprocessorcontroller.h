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
    void step();
    void controlProcess(); // called every process block
    bool interpolate();

private:

    RingBuffer<DataProcessorControllerCommand> dataProcessorControllerCommandBuffer_;
    std::vector<float> rowData;
    std::vector<float> nextRowData;
    std::vector<DataProcessor*> processors_;
    std::vector<DataProcessor*> nextValueProcessors_;
    std::vector<bool> interpolateFlags_;
    Dataset* dataset_;
    bool step_ = true;

    void processDataProcessorControllerCommand(DataProcessorControllerCommand cmd);
    void resize(uint size);
    void flush();
    float interpolateValue(const float first, const float second, const float mu);

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
