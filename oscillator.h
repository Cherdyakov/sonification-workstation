#ifndef QTOSCILLATOR_H
#define QTOSCILLATOR_H

#include "synthitem.h"
#include "parameterinterface.h"
#include "Gamma/Oscillator.h"

namespace sow {

class Oscillator : public SynthItem
{
    Q_OBJECT
    Q_PROPERTY(ParameterInterface* frequency READ frequencyInterface CONSTANT)
public:

    explicit Oscillator(QObject *parent = nullptr);

    ParameterInterface* frequencyInterface() const;

    virtual Frame process() override;

protected:

    ParameterInterface* frequencyInterface_;
    Parameter* frequency_;

    gam::Sine<float> gen_;

};

} // End namespace sow.

#endif // QTOSCILLATOR_H
