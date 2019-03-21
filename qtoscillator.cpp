#include "qtoscillator.h"

namespace sow {

QtOscillator::QtOscillator(QObject *parent) : QtSynthItem(parent)
{
    type_ = ENUMS::ITEM_TYPE::OSCILLATOR;
    outputType_ = ENUMS::OUTPUT_TYPE::AUDIO;

    frequency_ = new Parameter(this);
    frequencyInterface_ = new ParameterInterface(this);
    frequencyInterface_->connectInterface(frequency_);
    parameters_ = { frequency_ };
}

ParameterInterface* QtOscillator::frequencyInterface() const
{
    return frequencyInterface_;
}

Frame QtOscillator::process()
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
