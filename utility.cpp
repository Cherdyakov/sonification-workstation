#include "utility.h"

namespace sow {

// based on the Max "Scale" object
// https://docs.cycling74.com/max7/maxobject/scale
// default exp = 1 is linear
double scale(double x, double in_low, double in_high, double out_low, double out_high, double exp)
{
    return ((x-in_low)/(in_high-in_low) == 0) ? out_low : (((x-in_low)/(in_high-in_low)) > 0) ? (out_low + (out_high-out_low) * pow(((x-in_low)/(in_high-in_low)),exp)) : ( out_low + (out_high-out_low) * -(pow((((-x+in_low)/(in_high-in_low))),exp)));
}

Frame visit_children(std::vector<QtSynthItem*> children)
{
    Frame frame;
    for (unsigned int i = 0; i < children.size(); ++i)
    {
        QtSynthItem* gen = children[i];
        frame += gen->process();
    }
    frame /= children.size();
    return frame;
}

void insert_item_unique(QtSynthItem* synth_item, std::vector<QtSynthItem*>* items)
{
    if(std::find(items->begin(), items->end(), synth_item) == items->end())
    {
        items->push_back(synth_item);
    }
}

void remove_item(QtSynthItem* synth_item, std::vector<QtSynthItem*>* items)
{
    items->erase(std::remove(items->begin(), items->end(), synth_item), items->end());
}

void remove_as_child(QtSynthItem* self, std::vector<QtSynthItem *> parents)
{
    for(unsigned int i = 0; i < parents.size(); i++) {
        QtSynthItem* parent = parents[i];
        parent->removeChild(self);
    }
}

void remove_as_parent(QtSynthItem* self, std::vector<QtSynthItem*> children)
{
    for(unsigned int i = 0; i < children.size(); i++) {
        QtSynthItem* child = children[i];
        child->removeParent(self);
    }
}

bool verify_child(QtSynthItem::PARAMETER param, std::vector<QtSynthItem::PARAMETER> vec)
{
    return std::find(vec.begin(), vec.end(), param) != vec.end();
}

}// namespace sow
