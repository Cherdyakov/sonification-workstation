#ifndef PARAMETER_H
#define PARAMETER_H

#include <QObject>
#include "enums.h"
#include "ringbuffer.h"
#include "commands.h"
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
    void setData(const Dataset* dataset, const std::vector<float>* currentData);


private:

    // Backing variables.
    ENUMS::PARAMETER type_;
    QString name_ = "";
    bool scale_ = true;
    float scaleOutLow_ = 200.0f;
    float scaleOutHigh_ = 8000.0f;
    float scaleExponent_ = 1.0f;
    QString map_;
    std::vector<float>* data_ = nullptr;
    std::vector<float>* mins_ = nullptr;
    std::vector<float>* maxes_ = nullptr;
    RingBuffer<ParameterCommand> commandBuffer_;

    // Map expression evaulator.
    MapEvaluator<float> mapEvaluator_;

    virtual void processCommand(ParameterCommand cmd);
    virtual void processSetMap(std::string expression);

signals:

public slots:

    void onParameterChanged(const ENUMS::SUB_PARAMETER subParam, const float value);

};

} // namespace sow

#endif // PARAMETER_H
