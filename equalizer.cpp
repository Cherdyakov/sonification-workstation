#include "equalizer.h"

namespace sow {

Equalizer::Equalizer(QObject* parent) : SynthItem (parent)
{
    type_ = ENUMS::ITEM_TYPE::EQUALIZER;
    outputType_ = ENUMS::OUTPUT_TYPE::AUDIO;
    acceptedInputs_ = {
        ENUMS::OUTPUT_TYPE::AUDIO,
        ENUMS::OUTPUT_TYPE::AM
    };

    frequency_ = new ParameterFloat(this);
    frequencyInterface_ = new ParameterFloatInterface(this);
    frequencyInterface_->connectInterface(frequency_);
    parameters_.push_back(frequency_);

    resonance_ = new ParameterFloat(this);
    resonanceInterface_ = new ParameterFloatInterface(this);
    resonanceInterface_->connectInterface(resonance_);
    parameters_.push_back(resonance_);

    filterType_ = new ParameterIndex(this);
    filterTypeInterface_ = new ParameterIndexInterface(this);
    filterTypeInterface_->connectInterface(filterType_);
    parameters_.push_back(filterType_);

    resonanceInterface_->setMap("0.1");
    resonanceInterface_->setScaleOutLow(0.01f);
    resonanceInterface_->setScaleOutHigh(0.99f);

    resonanceInterface_->setMap("0.5");
    resonanceInterface_->setScaleOutLow(0.01f);
    resonanceInterface_->setScaleOutHigh(0.99f);

    filterTypeInterface_->setIdx(0);
}

ParameterFloatInterface* Equalizer::frequencyInterface()
{
    return frequencyInterface_;
}

ParameterFloatInterface* Equalizer::resonanceInterface()
{
    return resonanceInterface_;
}

ParameterIndexInterface *Equalizer::filterTypeInterface()
{
    return filterTypeInterface_;
}

Frame Equalizer::process()
{
    Frame frame;
    if(mute_) return frame;

    // Input frame.
    for (SynthItem*& child : children_) {
        if(child->outputType() == ENUMS::OUTPUT_TYPE::AUDIO) {
            frame += child->process();
        }
    }

    frame.left = biquadLeft(frame.left);
    frame.right = biquadRight(frame.right);

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
