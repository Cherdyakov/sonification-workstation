#include "synthgraph.h"
#include <QDebug>

namespace son {

SynthGraph::SynthGraph(QObject *parent) : QObject(parent)
{

}

QObject* SynthGraph::createItem(QObject* gui, int type)
{
    qDebug() << "createItem" << type;

    switch (type){
    case OUT: {
        break;
    }
    case OSCILLATOR: {
        SynthItem* item = new Oscillator();
        item->setGui(gui);
        return item;
        break;
    }
    default:
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

} //namespace son
