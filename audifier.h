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

private:

    // command buffering and parsing stuff
    void process_command(SynthItemCommand command);
    void process_add_child(SynthItem* child, PARAMETER parameter) override;
    void process_remove_child(SynthItem* child) override;
    void processSetIndexes(std::vector<int> indexes);
    void process_delete_item() override;
    float visitAmods();

};

}

#endif // AUDIFIER_H
