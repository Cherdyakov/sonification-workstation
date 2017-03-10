#include "qtsynthgraph.h"

QtSynthGraph::QtSynthGraph(QObject *parent) : QObject(parent)
{

}

SynthItem *QtSynthGraph::createItem(SynthItem::SON_ITEM_TYPE type)
{
    SynthItem* item = synthGraph.createItem(type);
    return item;
}

void QtSynthGraph::addToRoot(SynthItem *synthItem)
{
    synthGraph.addToRoot(synthItem);
}

void QtSynthGraph::removeFromRoot(SynthItem *synthItem)
{
    synthGraph.removeFromRoot(synthItem);
}

float QtSynthGraph::processGraph()
{
    float s;
    s = synthGraph.processGraph();
    return s;
}

int QtSynthGraph::graphSize()
{
    int size;
    size = synthGraph.graphSize();
    return size;
}

void QtSynthGraph::pause(bool pause)
{
    synthGraph.pause(pause);
}

void QtSynthGraph::setPos(double pos)
{
    synthGraph.setPos(pos);
}

void QtSynthGraph::setSpeed(double speed)
{
    synthGraph.setSpeed(speed);
}

void QtSynthGraph::setLooping(bool looping)
{
    synthGraph.setLooping(looping);
}

void QtSynthGraph::setLoopPoints(double begin, double end)
{
    synthGraph.setLoopPoints(begin, end);
}

void QtSynthGraph::setData(std::vector<double> *data, unsigned int height, unsigned int width)
{
    synthGraph.setData(data, height, width);
}

double QtSynthGraph::getPos()
{
    double pos;
    pos = synthGraph.getPos();
    return pos;
}
