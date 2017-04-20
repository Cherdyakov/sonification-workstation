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
    float process(float in) override;
    void addChild(SynthItem* child, ITEM_CHILD_TYPE type) override;
    void removeChild(SynthItem* child) override;
    void setIndexes(std::vector<int> indexes) override;

private:

    // command buffering and parsing stuff
    void processCommand(SynthItemCommand command);

    void processAddChild(SynthItem* child, ITEM_CHILD_TYPE type);
    void processRemoveChild(SynthItem* child);
    void processSetIndexes(std::vector<int> indexes);

    float visitAmods();

};

}

#endif // AUDIFIER_H
