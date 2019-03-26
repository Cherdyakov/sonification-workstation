#ifndef NOISE_H
#define NOISE_H

#include <QObject>
#include "synthitem.h"
#include "Gamma/Noise.h"
#include "parameterindexinterface.h"

namespace sow {

class Noise : public SynthItem
{
    Q_OBJECT
    Q_PROPERTY(ParameterIndexInterface* noise READ noiseTypeInterface CONSTANT)
public:

    explicit Noise(QObject *parent = nullptr);

    ParameterIndexInterface* noiseTypeInterface() const;

    virtual Frame process() override;

private:

    ParameterIndexInterface* noiseTypeInterface_;
    ParameterIndex* noiseType_;

    gam::NoiseWhite<> whiteNoise_;
    gam::NoisePink<> pinkNoise_;
    gam::NoiseBrown<> brownianNoise_;

signals:

    void noiseTypeChanged(ENUMS::NOISE noise);

};

} // namespace sow

#endif // NOISE_H
