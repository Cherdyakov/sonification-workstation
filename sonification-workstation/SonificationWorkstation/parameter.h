#ifndef PARAMETER_H
#define PARAMETER_H

#include <QObject>
#include "enums.h"
#include "ringbuffer.h"
#include "commands.h"

namespace sow {

class Parameter : public QObject
{
    Q_OBJECT
public:

    explicit Parameter(QObject *parent = nullptr);

    virtual void controlProcess();
    virtual void setData(const Dataset* dataset, const std::vector<float>* currentData);

protected:

    ENUMS::PARAMETER type_;
    RingBuffer<ParameterCommand> commandBuffer_;

    virtual void processCommand(const ParameterCommand cmd) = 0;

public slots:

    void onParameterChanged(const ENUMS::SUB_PARAMETER subParam, const float value);

};

} // namespace sow

#endif // PARAMETER_H
