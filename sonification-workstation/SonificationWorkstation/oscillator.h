#ifndef QTOSCILLATOR_H
#define QTOSCILLATOR_H

#include "synthitem.h"
#include "parameterfloatinterface.h"
#include "Gamma/Oscillator.h"

namespace sow {

class Oscillator : public SynthItem
{
    Q_OBJECT
    Q_PROPERTY(ParameterFloatInterface* frequency READ frequencyInterface CONSTANT)
public:

    explicit Oscillator(QObject *parent = nullptr);

    ParameterFloatInterface* frequencyInterface() const;

    virtual Frame process() override;

protected:

    ParameterFloatInterface* frequencyInterface_;
    ParameterFloat* frequency_;

    gam::Sine<float> gen_;

};

} // End namespace sow.

#endif // QTOSCILLATOR_H
