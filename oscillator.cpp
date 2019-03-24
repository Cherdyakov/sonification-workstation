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

    frequency_ = new Parameter(this);
    frequencyInterface_ = new ParameterInterface(this);
    frequencyInterface_->connectInterface(frequency_);
    parameters_ = { frequency_ };

}

ParameterInterface* Oscillator::frequencyInterface() const
{
    return frequencyInterface_;
}

Frame Oscillator::process()
{
    Frame frame;

    if(mute_)
    {
        return frame;
    }

    //set frequency of generator
    gen_.freq(frequency_->value());

    //generate frame

    // TODO: visit childreen and Apply AM or FM
    frame = gen_();

    return frame;
}

} // End namespace sow.
