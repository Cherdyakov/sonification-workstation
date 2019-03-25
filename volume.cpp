#include "volume.h"

namespace sow {

Volume::Volume(QObject *parent) : SynthItem(parent)
{
    type_ = ENUMS::ITEM_TYPE::VOLUME;
    outputType_ = ENUMS::OUTPUT_TYPE::AUDIO;
    acceptedInputs_ = {
        ENUMS::OUTPUT_TYPE::AUDIO,
        ENUMS::OUTPUT_TYPE::AM
    };

    amplitude_ = new Parameter(this);
    amplitudeInterface_ = new ParameterInterface(this);
    amplitudeInterface_->connectInterface(amplitude_);
    parameters_.push_back(amplitude_);

    // Amplitude should always scale from -1.0f to 1.0f.
    amplitudeInterface_->setScaleOutLow(-1.0f);
    amplitudeInterface_->setScaleOutHigh(1.0f);
    amplitudeInterface_->setMap("1.0");
}

ParameterInterface *Volume::amplitudeInterface() const
{
    return amplitudeInterface_;
}

Frame Volume::process()
{
    Frame frame;
    if(mute_) return frame;

    // Input frame.
    for (SynthItem*& child : children_) {
        if(child->outputType() == ENUMS::OUTPUT_TYPE::AUDIO) {
            frame += child->process();
        }
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

    return frame * amplitude_->value();
}

} // namespace son
