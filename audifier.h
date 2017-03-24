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
    void addChild(SynthItem* child, CHILD_TYPE type) override;
    void removeChild(SynthItem* child) override;
    void setDataItem(std::vector<double> *data) override;
    void setIndexes(std::vector<int> indexes) override;

private:

    // command buffering and parsing stuff
    void processCommand(SynthItemCommand command);

    void processAddChild(SynthItem* child, CHILD_TYPE type);
    void processRemoveChild(SynthItem* child);
    void processSetDataItem(std::vector<double> *data);
    void processSetIndexes(std::vector<int> indexes);
    void processMute(bool mute);

    std::vector<int> dataIndexes;
    std::vector<SynthItem*> amods;
    float visitAmods();

};

}

#endif // AUDIFIER_H
