#include "audifier.h"

namespace son {

Audifier::Audifier()
{
    myType = ITEM::AUDIFIER;

    acceptedChildren = {
        PARAMETER::AMPLITUDE
    };
}

float Audifier::process()
{
    float sample = 0.0;

    if(!commandBuffer.empty())
    {
        retrieveCommands();
    }
    if(muted)
    {
        return sample;
    }
    if(data)
    {
        for(unsigned int i = 0; i < dataIndexes.size(); i++)
        {
            // Audifier always scales datasets to range -1.0 to 1.0
            sample += scale((data->at(static_cast<unsigned int>(dataIndexes[i]))),
                            mins->at(i), maxes->at(i),
                            -1.0, 1.0);
        }
    }

    // vist amplitude modulating children
    if(!amods.empty())
    {
        float amSample = visitChildren(amods);
        sample *= amSample;
    }

    // divide by total number of datasets mapped (rows)
    // to prevent clipping
    return sample /  dataIndexes.size();
}

void Audifier::processCommand(SynthItemCommand command)
{
    COMMAND type = command.type;

    switch (type) {
    case COMMAND::INDEXES:
    {
        if(command.parameter == PARAMETER::AUDIFICATION)
        {
            processSetIndexes(command.ints);
        }
        break;
    }
    default:
        SynthItem::processCommand(command);
        break;
    }
}

void Audifier::processAddChild(SynthItem *child, PARAMETER parameter)
{
    switch (parameter){
    case PARAMETER::AMPLITUDE: {
        if(std::find(amods.begin(), amods.end(), child) != amods.end()) {
            return;
        } else {
            amods.push_back(child);
        }
        break;
    }
    default:
        break; //incompatible child type
    }
}

void Audifier::processRemoveChild(SynthItem *child)
{
    amods.erase(std::remove(amods.begin(), amods.end(), child), amods.end());
}

void Audifier::processSetIndexes(std::vector<int> indexes)
{
    bool m = muted;
    if(!muted) {
        muted = true;
    }
    dataIndexes = indexes;

    muted = m;
}

void Audifier::processDeleteItem()
{
    muted = true;

    for(unsigned int i = 0; i < parents.size(); i++) {
        SynthItem* parent = parents[i];
        parent->removeChild(this);
    }
    for(unsigned int i = 0; i < amods.size(); i++) {
        SynthItem* child = amods[i];
        child->removeParent(this);
    }

    delete this;
}

float Audifier::visitAmods()
{
    float sample = 0.0;
    for (unsigned int i = 0; i < amods.size(); ++i)
    {
        SynthItem* gen = amods[i];
        sample += gen->process();
    }
    return sample;
}

}
