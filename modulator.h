#ifndef MODULATOR_H
#define MODULATOR_H

#include "oscillator.h"

namespace son {

class Modulator : public Oscillator
{
public:
    Modulator();

    float process() override;
    void setModulationType(PARAMETER parameter);
    void setDepth(double depth);
    void setUseFixedDepth(bool fixed);
    void setUseDepthScaling(bool scaling);
    void setDepthScalingVals(double low, double high, double exp);

protected:
    void process_command(SynthItemCommand command) override;
    virtual void processSetDepth(double depth);
    void processSetUseFixedDepth(bool fixed);
    void processSetUseDepthScaling(bool scaling);
    void processSetDepthScalingVals(double low, double high, double exp);
    void set_gen_freqs();

private:
    double depth;
    bool useFixedDepth;

    //for scaling the data to depth values
    bool useDepthScaling;
    double depthScaleLow;
    double depthScaleHigh;
    double depthScaleExp;

    PARAMETER modType;
    void processSetModType(PARAMETER parameter);

    gam::AccumPhase<>* gen;

};

} // namespace son

#endif // MODULATOR_H
