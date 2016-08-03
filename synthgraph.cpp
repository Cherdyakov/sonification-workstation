#include "synthgraph.h"

namespace son {

SynthGraph::SynthGraph(QObject *parent, SynthItem *rt) : QObject(parent)
{
    root = rt;
}

void SynthGraph::insertItem(SynthItem *node)
{

}

float SynthGraph::processGraph()
{
    float s;

    s = root->process();

    //test noise
//    s = ((qrand() * 1.0 / RAND_MAX) - 1.0) * 0.2;
    //test mssg
//    qDebug() << "processGraph";

    return s;
}

} //namespace son
