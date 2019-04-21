#include "oscillator.h"

namespace sow {

Oscillator::Oscillator(QObject *parent) : SynthItem(parent)
{
    type_ = ENUMS::ITEM_TYPE::OSCILLATOR;
    outputType_ = ENUMS::OUTPUT_TYPE::AUDIO;
    acceptedInputs_ = {
        ENUMS::OUTPUT_TYPE::AM,
        ENUMS::OUTPUT_TYPE::FM
    };

    frequency_ = new ParameterFloat(this);
    frequencyInterface_ = new ParameterFloatInterface(this);
    frequencyInterface_->connectInterface(frequency_);
    parameters_.push_back(frequency_);

}

ParameterFloatInterface* Oscillator::frequencyInterface() const
{
    return frequencyInterface_;
}

Frame Oscillator::process()
{
    Frame frame;
    if(mute_) return frame;

    float freq = frequency_->value();

    // Frequency modulation.
    Frame fmFrame = 0.0f;
    bool fMod = false;
    for (SynthItem*& child : children_) {
        if(child->outputType() == ENUMS::OUTPUT_TYPE::FM) {
            fMod = true;
            fmFrame += child->process();
        }
    }
    if(fMod) freq += fmFrame.left;

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

    return frame;
}

} // End namespace sow.
