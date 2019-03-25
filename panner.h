#ifndef PANNER_H
#define PANNER_H

#include "synthitem.h"
#include "parameterinterface.h"

namespace sow {

class Panner : public SynthItem
{
    Q_OBJECT
    Q_PROPERTY(ParameterInterface* amplitude READ amplitudeInterface CONSTANT)
public:

    explicit Panner(QObject *parent = nullptr);

    ParameterInterface* amplitudeInterface() const;

    virtual Frame process() override;

private:

    ParameterInterface* amplitudeInterface_;
    Parameter* amplitude_;

signals:

public slots:
};

} // namespace sow

#endif // PAN_H
