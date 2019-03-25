#ifndef PANNER_H
#define PANNER_H

#include "synthitem.h"
#include "parameterinterface.h"

namespace sow {

class Panner : public SynthItem
{
    Q_OBJECT
    Q_PROPERTY(ParameterInterface* pan READ panInterface CONSTANT)
public:

    explicit Panner(QObject *parent = nullptr);

    ParameterInterface* panInterface() const;

    virtual Frame process() override;

private:

    ParameterInterface* panInterface_;
    Parameter* pan_;

signals:

public slots:
};

} // namespace sow

#endif // PAN_H
