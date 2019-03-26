#ifndef ENVELOPE_H
#define ENVELOPE_H

#include <QObject>
#include "Gamma/Envelope.h"
#include "synthitem.h"
#include "parameterfloatinterface.h"

namespace sow {

class Envelope : public SynthItem
{
    Q_OBJECT
    Q_PROPERTY(ParameterFloatInterface* attack READ attackInterface CONSTANT)
    Q_PROPERTY(ParameterFloatInterface* decay READ decayInterface CONSTANT)
public:

    explicit Envelope(QObject *parent = nullptr);

    ParameterFloatInterface* attackInterface() const;
    ParameterFloatInterface* decayInterface() const;

    virtual Frame process() override;

protected:

    virtual void step() override;

private:

    ParameterFloatInterface* attackInterface_;
    ParameterFloatInterface* decayInterface_;
    ParameterFloat* attack_;
    ParameterFloat* decay_;

    gam::AD<float> env_;

};

} // namespace sow

#endif // ENVELOPE_H
