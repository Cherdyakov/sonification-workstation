#include "utility.h"

namespace sow {

// based on the Max "Scale" object
// https://docs.cycling74.com/max7/maxobject/scale
// default exp = 1 is linear
double scale(double x, double in_low, double in_high, double out_low, double out_high, double exp)
{
    return ((x-in_low)/(in_high-in_low) == 0) ? out_low : (((x-in_low)/(in_high-in_low)) > 0) ? (out_low + (out_high-out_low) * pow(((x-in_low)/(in_high-in_low)),exp)) : ( out_low + (out_high-out_low) * -(pow((((-x+in_low)/(in_high-in_low))),exp)));
}

Frame visit_children(std::vector<SynthItem*> children)
{
    Frame frame;
    for (unsigned int i = 0; i < children.size(); ++i)
    {
        SynthItem* gen = children[i];
        frame += gen->process();
    }
    frame /= children.size();
    return frame;
}

void insert_item_unique(SynthItem* synth_item, std::vector<SynthItem*>* items)
{
    if(std::find(items->begin(), items->end(), synth_item) == items->end())
    {
        items->push_back(synth_item);
    }
}

void remove_item(SynthItem* synth_item, std::vector<SynthItem*>* items)
{
    items->erase(std::remove(items->begin(), items->end(), synth_item), items->end());
}

void remove_as_child(SynthItem* self, std::vector<SynthItem *> parents)
{
    for(unsigned int i = 0; i < parents.size(); i++) {
        SynthItem* parent = parents[i];
        parent->remove_child(self);
    }
}

void remove_as_parent(SynthItem* self, std::vector<SynthItem*> children)
{
    for(unsigned int i = 0; i < children.size(); i++) {
        SynthItem* child = children[i];
        child->remove_parent(self);
    }
}

bool verify_child(SynthItem::PARAMETER param, std::vector<SynthItem::PARAMETER> vec)
{
    return std::find(vec.begin(), vec.end(), param) != vec.end();
}

}// namespace sow
