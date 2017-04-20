#ifndef MODULATOR_H
#define MODULATOR_H

#include "oscillator.h"
#include "modulatorcommand.h"

namespace son {

class Modulator : public Oscillator
{
public:
    Modulator();
    void setModType(ITEM_CHILD_TYPE childType);

protected:
    virtual void processCommand(SynthItemCommand command) override;

private:
    ITEM_CHILD_TYPE modType;
    void processSetModType(ITEM_CHILD_TYPE childType);

};

} // namespace son

#endif // MODULATOR_H
