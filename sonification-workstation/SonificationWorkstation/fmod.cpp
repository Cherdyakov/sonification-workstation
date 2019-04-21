#include "fmod.h"

namespace sow {

Fmod::Fmod(QObject *parent) : Oscillator(parent)
{
    type_ = ENUMS::ITEM_TYPE::FMOD;
    outputType_ = ENUMS::OUTPUT_TYPE::FM;
    acceptedInputs_ = {
        ENUMS::OUTPUT_TYPE::AM
    };

    depth_ = new ParameterFloat(this);
    depthInterface_ = new ParameterFloatInterface(this);
    depthInterface_->connectInterface(depth_);
    parameters_.push_back(depth_);

    depthInterface_->setMap("100");
}

ParameterFloatInterface *Fmod::depthInterface() const
{
    return depthInterface_;
}

Frame Fmod::process()
{
    Frame frame;
    if(mute_) return frame;

    float freq = frequency_->value();

    //set frequency of generator
    gen_.freq(freq);

    //Generate frame.
    frame = gen_();

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
    frame *= depth_->value();

    return frame;
}

} // namespace sow
