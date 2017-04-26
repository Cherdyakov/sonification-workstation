#ifndef AUDIFIER_H
#define AUDIFIER_H

#include <algorithm>

#include "synthitem.h"
#include "ringbuffer.h"

namespace son {

class Audifier : public SynthItem
{

public:
    Audifier();
    float process() override;
    void removeChild(SynthItem* child) override;

private:

    // command buffering and parsing stuff
    void processCommand(SynthItemCommand command);
    void processAddChild(SynthItem* child, PARAMETER parameter) override;
    void processRemoveChild(SynthItem* child) override;
    void processSetIndexes(std::vector<int> indexes);
    void processDeleteItem() override;
    float visitAmods();

};

}

#endif // AUDIFIER_H
