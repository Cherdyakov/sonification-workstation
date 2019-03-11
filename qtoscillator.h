#ifndef QTOSCILLATOR_H
#define QTOSCILLATOR_H

#include "qtsynthitem.h"
#include "parameter.h"
#include "parameterinterface.h"
#include "Gamma/Oscillator.h"

namespace sow {

class QtOscillator : public QtSynthItem
{
    Q_OBJECT
    Q_PROPERTY(ParameterInterface* frequency READ frequencyInterface CONSTANT)
public:

    explicit QtOscillator(QObject *parent = nullptr);

    ParameterInterface* frequencyInterface() const;

    Frame process();

private:

    ParameterInterface* frequencyInterface_;
    Parameter* frequency_;

    gam::Sine<float> gen_;

};

} // End namespace sow.

#endif // QTOSCILLATOR_H
