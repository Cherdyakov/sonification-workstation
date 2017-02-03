#include "audifier.h"

namespace son {

Audifier::Audifier()
{

}

float Audifier::process()
{
    float s = 0.0;

    s = (dataColumn->at(0) / 1000000000.0);

//    for(int i = 0; i < dataIndexes.count(); i++) {
////        qDebug() << dataColumn->at(dataIndexes[i]);
//        s = (dataColumn->at(dataIndexes[i]) / 32800.0) * 0.2;
//    }

    //visit amods eventually goes here
    return s;
}

void Audifier::addChild(QObject *child, SynthItem::CHILD_TYPE type)
{
    SynthItem* item = static_cast<SynthItem*>(child);

    switch (type){
    case AMOD: {
        if(!amods.contains(item))
        {
            return; //already child
        }
        amods.push_back(item);
        break;
    }
    default:
        break; //incompatible child type
    }
}

void Audifier::removeChild(QObject *child)
{
    SynthItem* item = static_cast<SynthItem*>(child);

    int idx;

    idx = amods.indexOf(item);
    if(idx > -1)
    {
        amods.remove(idx);
        return;
    }
}

void Audifier::setDataColumn(QVector<double> *col)
{
    dataColumn = col;

    for(int i = 0; i < amods.count(); i++) {
        son::SynthItem* item = amods[i];
        item->setDataColumn(col);
    }
}

bool Audifier::setIndexes(QVector<int> idxs)
{
    bool m = muted;
    if(!muted) {
        muted = true;
    }
    dataIndexes = idxs;
    qDebug() << "aud dataIndexes: " << dataIndexes;

    muted = m;
}

float Audifier::visitAmods()
{
    float s = 0.0;
    QVector<SynthItem*>::const_iterator i;

    for (i = amods.constBegin(); i != amods.constEnd(); ++i)
    {
        SynthItem* gen = *i;
        s += gen->process();
    }
    return s;
}

}
