#ifndef AUDIFIER_H
#define AUDIFIER_H

#include <algorithm>

#include "synthitem.h"
#include "ringbuffer.h"
#include "audifiercommand.h"

namespace son {

class Audifier : public SynthItem
{

public:
    Audifier();
    float process() override;
    float process(float in) override;

private:

    // command buffering and parsing stuff
    AudifierCommand currentCommand;
    void retrieveCommands();
    void processCommand(AudifierCommand command);
    RingBuffer<AudifierCommand> commandBuffer;

    void processAddChild(SynthItem* child, CHILD_TYPE type);
    void processRemoveChild(SynthItem* child);
    void processSetDataItem(std::vector<double> *data);
    void processSetIndexes(std::vector<int> indexes);
    void processMute(bool mute);

    std::vector<int> dataIndexes;
    std::vector<SynthItem*> amods;
    float visitAmods();
    void resize(unsigned int size);

};

} // namespace son

#endif // AUDIFIER_H
