#ifndef AUDIFIER_H
#define AUDIFIER_H

#include <algorithm>

#include "synthitem.h"

namespace son {

class Audifier : public SynthItem
{

public:
    Audifier();
    float process() override;
    void addChild(SynthItem *child, SynthItem::SON_CHILD_TYPE type) override;
    void removeChild(SynthItem* child) override;
    void setDataItem(std::vector<double> *data) override;
    void setIndexes(std::vector<int> indexes) override;

private:

    std::vector<int> dataIndexes;
    std::vector<SynthItem*> amods;
    float visitAmods();
    void resize(unsigned int size);

};

}

#endif // AUDIFIER_H
