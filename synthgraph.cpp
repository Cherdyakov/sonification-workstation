#include "synthgraph.h"
#include <QDebug>

namespace son {

SynthGraph::SynthGraph(QObject *parent) : QObject(parent)
{
    paused = true;
    looping = false;
    ringBuffer = NULL;
    ringBufferSize = 2048;
    blockSize = 512;
    sr = 44100;
    dataWidth = 0;
    dataHeight = 0;
    playheadIdx = 0;
    mu = 0.0;
    speed = 1.0;
}

QObject* SynthGraph::createItem(QObject* gui, SYNTH_ITEM_TYPE type)
{
    SynthItem* item;

    switch (type){
    case OUT: {
        item = NULL;
        break;
    }
    case OSCILLATOR: {
        item = new Oscillator();
        item->setGui(gui);
        item->setDataItem(&currentData);
        break;
    }
    case AUDIFIER: {
        item = new Audifier();
        item->setGui(gui);
        item->setDataItem(&currentData);
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

double SynthGraph::processGraph()
{
    float s = 0.0;

    if(paused) {
        return s;
    }

    // updating playheadIdx
    if(mu >= 1.0)
    {
        mu -= 1.0;
        playheadIdx++;
        if(playheadIdx > (dataWidth - 1))
        {
            playheadIdx = 0;
        }
        retrieveData();
    }

    QVector<SynthItem*>::const_iterator i;

    for (i = graphRoot.constBegin(); i != graphRoot.constEnd(); ++i) {
        SynthItem* item = *i;
        s += item->process();
    }

    // advancing playhead
    mu += (speed / sr);

    //Test Noise
//    s = ((qrand() * 1.0 / RAND_MAX) - 1.0) * 0.2;

    return s;
}

int SynthGraph::graphSize()
{
    return graphRoot.count();
}

void SynthGraph::pause(bool p)
{
    if(!p)
    {
        retrieveData();
    }
    paused = p;
}

void SynthGraph::loop(bool l)
{
    looping = l;
}

void SynthGraph::setPos(double p)
{
    playheadIdx = (int)p;
    mu = (p - playheadIdx);
}

double SynthGraph::getPos()
{
    double pos = ((double)playheadIdx + mu);
    return pos;
}

void SynthGraph::setLoopPoints(unsigned int begin, unsigned int end)
{
    loopBegin = begin;
    loopEnd = end;
}

void SynthGraph::setSpeed(double s)
{
    speed = s;
}

void SynthGraph::setData(std::vector<double> *d, unsigned int height, unsigned int width)
{
    data = d;
    dataWidth = width;
    currentData.clear();
    playheadIdx = 0;
    mu = 0.0;

    if(dataHeight != height)
    {
        dataHeight = height;
        currentData.resize(dataHeight);
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
    for(unsigned int i = 0; i < dataHeight; i++)
    {
        unsigned int idx = ((dataWidth * i) + playheadIdx);
        currentData[i] = (*data)[idx];
    }
}

} //namespace son
