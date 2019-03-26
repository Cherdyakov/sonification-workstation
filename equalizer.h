#ifndef EQUALIZER_H
#define EQUALIZER_H

#include <QObject>
#include "Gamma/Filter.h"
#include "synthitem.h"
#include "parameterfloatinterface.h"
#include "parameterindexinterface.h"

namespace sow {

class Equalizer : public SynthItem
{
    Q_OBJECT
    Q_PROPERTY(ParameterFloatInterface* frequency READ frequencyInterface CONSTANT)
    Q_PROPERTY(ParameterFloatInterface* resonance READ resonanceInterface CONSTANT)
    Q_PROPERTY(ParameterIndexInterface* filterType READ filterTypeInterface CONSTANT)
public:
    explicit Equalizer(QObject* parent);

    ParameterFloatInterface* frequencyInterface();
    ParameterFloatInterface* resonanceInterface();
    ParameterIndexInterface* filterTypeInterface();

    virtual Frame process() override;

private:

    ParameterFloatInterface* frequencyInterface_;
    ParameterFloat* frequency_;
    ParameterFloatInterface* resonanceInterface_;
    ParameterFloat* resonance_;
    ParameterIndexInterface* filterTypeInterface_;
    ParameterIndex* filterType_;

    gam::Biquad<> biquadLeft;
    gam::Biquad<> biquadRight;

};

} // namespace sow

#endif // EQUALIZER_H
