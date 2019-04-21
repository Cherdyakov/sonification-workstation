#include "noise.h"

namespace sow {

Noise::Noise(QObject *parent) : SynthItem(parent)
{
    type_ = ENUMS::ITEM_TYPE::NOISE_GEN;
    outputType_ = ENUMS::OUTPUT_TYPE::AUDIO;
    acceptedInputs_ = {
        ENUMS::OUTPUT_TYPE::AM
    };

    noiseType_ = new ParameterIndex(this);
    noiseTypeInterface_ = new ParameterIndexInterface(this);
    noiseTypeInterface_->connectInterface(noiseType_);
    parameters_.push_back(noiseType_);
}

ParameterIndexInterface *Noise::noiseTypeInterface() const
{
    return noiseTypeInterface_;
}


Frame Noise::process()
{
    Frame frame;
    if(mute_) return frame;

    ENUMS::NOISE type = static_cast<ENUMS::NOISE>(noiseType_->idx());

    switch (type) {
    case ENUMS::NOISE::WHITE:
        frame = whiteNoise_();
        break;
    case ENUMS::NOISE::PINK:
        frame = pinkNoise_();
        break;
    case ENUMS::NOISE::BROWNIAN:
        frame = brownianNoise_();
        break;
    }

    // Amplitude modulation.
    Frame amFrame = 0.0f;
    bool aMod = false;
    for (SynthItem*& child : children_) {
        if(child->outputType() == ENUMS::OUTPUT_TYPE::AM) {
            aMod = true;
            amFrame += child->process();
        }
    }

    if(aMod) frame *= amFrame;

    return frame;
}

} // namespace sow
