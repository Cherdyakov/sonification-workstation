#include "audifier.h"

namespace son {

Audifier::Audifier()
{

}

float Audifier::process()
{
    float s = 0.0;

    s = (dataItem->at(0) / 1000000000.0);

//    for(int i = 0; i < dataIndexes.count(); i++) {
////        qDebug() << dataColumn->at(dataIndexes[i]);
//        s = (dataColumn->at(dataIndexes[i]) / 32800.0) * 0.2;
//    }

    //visit amods eventually goes here
    return s;
}

void Audifier::addChild(SynthItem *child, SON_CHILD_TYPE type)
{

    switch (type){
    case SON_CHILD_TYPE::AMOD: {
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

void Audifier::removeChild(SynthItem *child)
{
    amods.erase(std::remove(amods.begin(), amods.end(), child), amods.end());
}

void Audifier::setDataItem(std::vector<double> *data)
{
    dataItem = data;
    for(unsigned int i = 0; i < amods.size(); i++) {
        son::SynthItem* item = amods[i];
        item->setDataItem(data);
    }
}

void Audifier::setIndexes(std::vector<int> indexes)
{
    bool m = muted;
    if(!muted) {
        muted = true;
    }
    dataIndexes = indexes;

    resize(dataIndexes.size());

    muted = m;
}

float Audifier::visitAmods()
{
    float s = 0.0;
    for (unsigned int i = 0; i < amods.size(); ++i)
    {
        SynthItem* gen = amods[i];
        s += gen->process();
    }
    return s;
}

void Audifier::resize(unsigned int size)
{
    // resize
}

}
