#include "synthgraph.h"
#include <QDebug>

namespace son {

SynthGraph::SynthGraph(QObject *parent) : QObject(parent)
{
    paused = true;
    ringBuffer = NULL;
    ringBufferSize = 2048;
    blockSize = 512;
    audioRate = 44100;
    dataDimensions = 0;
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
        item->setDataItem(&dataItem);
        break;
    }
    case AUDIFIER: {
        item = new Audifier();
        item->setGui(gui);
        item->setDataItem(&dataItem);
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

    if(paused) {
        return s;
    }

    retrieveData();

    QVector<SynthItem*>::const_iterator i;

    for (i = graphRoot.constBegin(); i != graphRoot.constEnd(); ++i) {
        SynthItem* item = *i;
        s += item->process();
    }

    //Test Noise
    {
        //test noise
        //    s = ((qrand() * 1.0 / RAND_MAX) - 1.0) * 0.2;
        //test mssg
        //    qDebug() << "processGraph";
    }

    return s;
}

int SynthGraph::graphSize()
{
    return graphRoot.count();
}

void SynthGraph::pause(bool p)
{
    if(paused != p) {
        paused = p;
    }
}

void SynthGraph::setDimensions(int dimensions)
{
    if(dataDimensions != dimensions)
    {
        dataDimensions = dimensions;
    }
}

void SynthGraph::setSpeed(int s)
{
    if(speed != s)
    {
        //speed is data samples to use per second
        speed = s;
        srcRatio = audioRate / (double)speed;
    }
}

void SynthGraph::ringBufferInit(int capacity, int channels)
{
    if(ringBuffer)
    {
        delete ringBuffer;
        ringBuffer = NULL;
    }
    ringBuffer = new RingBuffer(capacity, channels);
}

void SynthGraph::retrieveData()
{
    static unsigned int numSamples;

    if(ringBuffer->empty())
    {
        qDebug() << "graph: ringbuffer empty!";
        return;
    }

    if(ringBuffer->pop(&dataItem))
    {
        *itemsRead++;
    }
    //    qDebug() << "graph: " << dataColumn;
}

} //namespace son
