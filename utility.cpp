#include "utility.h"

namespace son {

// based on the Max "Scale" object
// https://docs.cycling74.com/max7/maxobject/scale
// default exp = 1 is linear
double scale(double x, double in_low, double in_high, double out_low, double out_high, double exp)
{
    return ((x-in_low)/(in_high-in_low) == 0) ? out_low : (((x-in_low)/(in_high-in_low)) > 0) ? (out_low + (out_high-out_low) * pow(((x-in_low)/(in_high-in_low)),exp)) : ( out_low + (out_high-out_low) * -(pow((((-x+in_low)/(in_high-in_low))),exp)));
}

float visit_children(std::vector<SynthItem*> children)
{
    float s = 0.0;
    for (unsigned int i = 0; i < children.size(); ++i)
    {
        SynthItem* gen = children[i];
        s += gen->process();
    }
    s /= children.size();
    return s;
}

void insert_item_unique(SynthItem* synth_item, std::vector<SynthItem*> items)
{
    if(std::find(items.begin(), items.end(), synth_item) == items.end())
    {
        items.push_back(synth_item);
    }
}

void erase_item(SynthItem* synth_item, std::vector<SynthItem*> items)
{
    items.erase(std::remove(items.begin(), items.end(), synth_item), items.end());
}

void remove_as_child(SynthItem* self, std::vector<SynthItem*> parents)
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

}// namespace son
