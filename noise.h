#ifndef NOISE_H
#define NOISE_H

#include <QObject>
#include "synthitem.h"
#include "Gamma/Noise.h"
#include "parameterfloatinterface.h"

namespace sow {

class Noise : public SynthItem
{
    Q_OBJECT
    Q_PROPERTY(ENUMS::NOISE noiseType READ noiseType WRITE setNoiseType NOTIFY noiseTypeChanged)
public:

    explicit Noise(QObject *parent = nullptr);

    ENUMS::NOISE noiseType() const;
    void setNoiseType(ENUMS::NOISE noiseType);

    virtual Frame process() override;

private:

    ENUMS::NOISE noiseType_;

    gam::NoiseWhite<> whiteNoise_;
    gam::NoisePink<> pinkNoise_;
    gam::NoiseBrown<> brownianNoise_;

signals:

    void noiseTypeChanged(ENUMS::NOISE noise);

};

} // namespace sow

#endif // NOISE_H
