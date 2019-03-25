#ifndef ENVELOPE_H
#define ENVELOPE_H

#include <QObject>
#include "Gamma/Envelope.h"
#include "synthitem.h"
#include "parameterinterface.h"

namespace sow {

class Envelope : public SynthItem
{
    Q_OBJECT
    Q_PROPERTY(ParameterInterface* attack READ attackInterface CONSTANT)
    Q_PROPERTY(ParameterInterface* decay READ decayInterface CONSTANT)
public:

    explicit Envelope(QObject *parent = nullptr);

    ParameterInterface* attackInterface() const;
    ParameterInterface* decayInterface() const;

    virtual Frame process() override;

protected:

    virtual void step() override;

private:

    ParameterInterface* attackInterface_;
    ParameterInterface* decayInterface_;
    Parameter* attack_;
    Parameter* decay_;

    gam::AD<float> env_;

};

} // namespace sow

#endif // ENVELOPE_H
