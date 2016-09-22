#include "synthgraph.h"
#include <QDebug>

namespace son {

SynthGraph::SynthGraph(QObject *parent) : QObject(parent)
{
    root = NULL;
    //    root = rt;
}

QObject* SynthGraph::createItem(QObject* gui, int type)
{
    qDebug() << "createItem" << type;

    switch (type){
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

void SynthGraph::connect(SynthItem *parent, SynthItem* child)
{
    qDebug() << "connect";

}

float SynthGraph::processGraph()
{
    float s = 0.0;

    if(root == NULL)
    {
        return s;
    }

    s = root->process();


    //test noise
    //    s = ((qrand() * 1.0 / RAND_MAX) - 1.0) * 0.2;
    //test mssg
    //    qDebug() << "processGraph";

    return s;
}

} //namespace son
