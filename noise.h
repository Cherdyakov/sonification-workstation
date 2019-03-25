#ifndef NOISE_H
#define NOISE_H

#include <QObject>
#include "synthitem.h"
#include "Gamma/Noise.h"
#include "parameterinterface.h"

namespace sow {

class Noise : public SynthItem
{
    Q_OBJECT
    Q_PROPERTY(ParameterInterface* noise READ noiseInterface CONSTANT)
public:

    explicit Noise(QObject *parent = nullptr);

    ParameterInterface* noiseInterface() const;

    virtual Frame process() override;

private:

    ParameterInterface* noiseInterface_;
    Parameter* noise_;

    gam::NoiseWhite<> whiteNoise_;
    gam::NoisePink<> pinkNoise_;
    gam::NoiseBrown<> brownianNoise_;
};

} // namespace sow

#endif // NOISE_H
