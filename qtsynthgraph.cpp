#include "qtsynthgraph.h"

QtSynthGraph::QtSynthGraph(QObject *parent) : QObject(parent)
{

}

void QtSynthGraph::addToRoot(QtSynthItem *qtSynthItem)
{
    synthGraph.addToRoot(qtSynthItem->implementation());
}

void QtSynthGraph::removeFromRoot(QtSynthItem *qtSynthItem)
{
    synthGraph.removeFromRoot(qtSynthItem->implementation());
}

QtSynthItem* QtSynthGraph::createItem(ITEM_TYPE type)
{
    SynthItem* item = NULL;
    QtSynthItem* qtItem = NULL;

    switch (type){
    case ITEM_TYPE::OUT:
    {
        break;
    }
    case OSCILLATOR:
    {
        item = synthGraph.createItem((SynthItem::ITEM_TYPE)type);
        qtItem = new QtOscillator(item);
        break;
    }
    case AUDIFIER:
    {
        item = synthGraph.createItem((SynthItem::ITEM_TYPE)type);
        qtItem = new QtAudifier(item);
        break;
    }
    default:
        break;
    }
    return qtItem;
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
