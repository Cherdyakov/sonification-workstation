#ifndef PARAMETER_H
#define PARAMETER_H

#include <QObject>
#include "enums.h"
#include "ringbuffer.h"
#include "commands.h"
#include "scaler.h"
#include "mapevaluator.h"
#include "utility.h"

namespace sow {

class Parameter : public QObject
{
    Q_OBJECT
public:

    explicit Parameter(QObject *parent = nullptr);

    float value();
    void controlProcess();
    bool setMap(const QString map);
    virtual void setData(std::vector<float>* const data,
                         std::vector<float>* const mins,
                         std::vector<float>* const maxes);

private:

    // Backing variables.
    ENUMS::PARAMETER type_;
    QString name_ = "";
    bool scale_ = true;
    Scaler<float> scaler_;
    QString map_;
    std::vector<float>* data_ = nullptr;
    std::vector<float>* mins_ = nullptr;
    std::vector<float>* maxes_ = nullptr;
    RingBuffer<ParameterCommand> commandBuffer_;
    RingBuffer<DatasetCommand> datasetCommandBuffer_;

    // Map expression evaulator.
    MapEvaluator<float> evaluator_;

    virtual void processCommand(ParameterCommand cmd);
    virtual void processDatasetCommand(DatasetCommand cmd);
    virtual void processSetMap(std::string expression);

signals:

public slots:

    void onParameterChanged(const ENUMS::SUB_PARAMETER subParam, const float value);

};

} // namespace sow

#endif // PARAMETER_H
