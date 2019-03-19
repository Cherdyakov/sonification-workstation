#ifndef PARAMETER_H
#define PARAMETER_H

#include <QObject>
#include "enums.h"
#include "ringbuffer.h"
#include "commands.h"
#include "scaler.h"
#include "mapevaluator.h"

namespace sow {

class Parameter : public QObject
{
    Q_OBJECT
public:

    explicit Parameter(QObject *parent = nullptr);

    float value();
    void controlProcess();
    bool setMap(const QString map);

private:

    // Backing variables
    ENUMS::PARAMETER type_;
    QString name_;
    float value_;
    bool fixed_;
    bool scale_;
    Scaler<float> scaler_;
    QString map_;

    // For processing ParameterCommands
    RingBuffer<ParameterCommand> commandBuffer_;
    void processCommand(ParameterCommand cmd);

signals:

public slots:

    void onParameterChanged(const ENUMS::SUB_PARAMETER subParam, const float value);

};

} // namespace sow

#endif // PARAMETER_H
