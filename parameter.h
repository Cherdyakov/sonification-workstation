#ifndef PARAMETER_H
#define PARAMETER_H

#include <QObject>
#include "sowenums.h"
#include "ringbuffer.h"
#include "commands.h"
#include "parameterinterface.h"

namespace sow {

class Parameter : public QObject
{
    Q_OBJECT
public:
    explicit Parameter(QObject *parent = nullptr);

    void connectInterface(ParameterInterface* interface);
    void controlProcess();

private:

    // Backing variables, used by sow
    SowEnums::PARAMETER type_;
    QString name_;
    float value_;
    bool fixed_;
    bool scaled_;
    float scaleLo_;
    float scaleHi_;
    float scaleExp_;
    QString map_;

    // For processing ParameterCommands
    RingBuffer<ParameterCommand> commandBuffer_;
    ParameterCommand currentCommand_;

    void processCommand(ParameterCommand cmd);

signals:

public slots:
    void onParameterChanged(const SowEnums::SUB_PARAMETER subParam, const float value);
    void onMapChanged(const QString map);

};

} // namespace sow

#endif // PARAMETER_H
