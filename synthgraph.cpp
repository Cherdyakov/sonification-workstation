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
        return item;
        break;
    }
    case OSCILLATOR: {
        item = new Oscillator();
        item->setGui(gui);
        return item;
        break;
    }
    default:
        item = NULL;
        return item;
        break;
    }
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

    dataColumn = retrieveDataColumn();

    if(dataColumn)
    {
        qDebug() << "graph: " << *dataColumn;
    }

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

QVector<double>* SynthGraph::retrieveDataColumn()
{
    if(ringBuffer)
    {
        QVector<double>* col;
        col = ringBuffer->pop();
        return col;
    }

    return NULL;
}

int SynthGraph::graphSize()
{
    return graphRoot.count();
}

void SynthGraph::setRingBuffer(RingBuffer *buffer)
{
    ringBuffer = buffer;
}

} //namespace son
