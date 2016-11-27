#include "synthgraph.h"
#include <QDebug>

namespace son {

SynthGraph::SynthGraph(QObject *parent) : QObject(parent)
{

}

QObject* SynthGraph::createItem(QObject* gui, SYNTH_ITEM_TYPE type)
{
    //    qDebug() << "createItem" << type;

    SynthItem* item;

    switch (type){
    case OUT: {
        item = NULL;
        break;
    }
    case OSCILLATOR: {
        item = new Oscillator();
        item->setGui(gui);
        item->setDataColumn(&dataColumn);
        break;
    }
    default:
        item = NULL;
        break;
    }
    return item;
}

void SynthGraph::addToRoot(SynthItem *synthItem)
{
    SynthItem* item = static_cast<SynthItem*>(synthItem);
    if(!graphRoot.contains(item))
    {
        graphRoot.push_back(item);
    }
}

void SynthGraph::removeFromRoot(SynthItem *synthItem)
{
    SynthItem* item = static_cast<SynthItem*>(synthItem);

    int idx;

    idx = graphRoot.indexOf(item);
    if(idx > -1)
    {
        graphRoot.remove(idx);
        return;
    }
}

float SynthGraph::processGraph()
{
    float s = 0.0;

    retrieveData();

    QVector<SynthItem*>::const_iterator i;

    for (i = graphRoot.constBegin(); i != graphRoot.constEnd(); ++i) {
        SynthItem* item = *i;
        s += item->process();
    }


    //test noise
    //    s = ((qrand() * 1.0 / RAND_MAX) - 1.0) * 0.2;
    //test mssg
    //    qDebug() << "processGraph";

    return s;
}

int SynthGraph::graphSize()
{
    return graphRoot.count();
}

void SynthGraph::setRingBuffer(RingBuffer *buffer)
{
    ringBuffer = buffer;
}

void SynthGraph::retrieveData()
{

    if(!ringBuffer->empty())
    {
        dataColumn = ringBuffer->pop();
        qDebug() << "graph: retrieveData: " << dataColumn;
    }
}

} //namespace son
