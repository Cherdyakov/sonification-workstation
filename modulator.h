#ifndef MODULATOR_H
#define MODULATOR_H

#include "oscillator.h"
#include "modulatorcommand.h"

namespace son {

class Modulator : public Oscillator
{
public:
    Modulator();

    float process() override;

    void setModType(CHILD_TYPE modType);

private:
    CHILD_TYPE modType;


    void processSetModType(CHILD_TYPE modType);

};

} // namespace son

#endif // MODULATOR_H
