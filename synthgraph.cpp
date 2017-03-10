#include "synthgraph.h"

namespace son {

SynthGraph::SynthGraph()
{
    paused = true;
    looping = false;
    loopBegin = 0.0;
    loopEnd = 0.0;
    dataStale = false;
    ringBufferSize = 2048;
    blockSize = 512;
    sr = 44100;
    dataWidth = 0;
    dataHeight = 0;
    currentIdx = 0;
    mu = 0.0;
    speed = 1.0;
    returnPos = 0.0;
    masterVolume = 1.0;
}

float SynthGraph::processGraph()
{
    float s = 0.0;

    if(!commandBuffer.empty())
    {
        retrieveCommands();
    }

    if(paused)
    {
        calculateReturnPos();
        return s;
    }

    // updating playheadPos
    if(mu >= 1.0)
    {
        mu -= 1.0;
        currentIdx++;

        if((currentIdx + 1) > (dataWidth))
        {
            currentIdx = 0;
        }
        dataStale = true;
    }

    if(looping && (loopBegin != loopEnd))
    {
        if(((double)currentIdx + mu) > loopEnd)
        {
            currentIdx = (int)loopBegin;
            mu = (loopBegin - currentIdx);
            dataStale = true;
        }
        else if(((double)currentIdx + mu) < loopBegin)
        {
            currentIdx = (int)loopBegin;
            mu = (loopBegin - currentIdx);
            dataStale = true;
        }
    }

    if(dataStale)
    {
        retrieveData();
        dataStale = false;
    }

    std::vector<SynthItem*>::const_iterator i;

    for (int i = 0; i < graphRoot.size(); ++i) {
        SynthItem* item = graphRoot[i];
        s += item->process();
    }

    // advancing index
    calculateReturnPos();
    mu += (speed / sr);

    return s * masterVolume;
}

SynthItem* SynthGraph::createItem(SynthItem::SON_ITEM_TYPE type)
{
    SynthItem* item;

    switch (type){
    case SynthItem::SON_ITEM_TYPE::OUT:
    {
        item = NULL;
        break;
    }
    case SynthItem::SON_ITEM_TYPE::OSCILLATOR:
    {
        item = new Oscillator();
        item->setDataItem(&currentData);
        break;
    }
    case SynthItem::SON_ITEM_TYPE::AUDIFIER:
    {
        item = new Audifier();
        item->setDataItem(&currentData);
        break;
    }
    default:
        item = NULL;
        break;
    }
    return item;
}

void SynthGraph::addToRoot(SynthItem *child)
{
    if(std::find(graphRoot.begin(), graphRoot.end(), child) != graphRoot.end()) {
        return;
    } else {
        graphRoot.push_back(child);
    }
}

void SynthGraph::removeFromRoot(SynthItem *child)
{
    graphRoot.erase(std::remove(graphRoot.begin(), graphRoot.end(), child), graphRoot.end());
}

int SynthGraph::graphSize()
{
    return graphRoot.size();
}

void SynthGraph::pause(bool pause)
{
    SynthCommand command;
    command.type = SynthCommandType::PAUSE;
    command.paused = pause;
    commandBuffer.push(command);
}

void SynthGraph::setLooping(bool looping)
{
    SynthCommand command;
    command.type = SynthCommandType::LOOP;
    command.looping = looping;
    commandBuffer.push(command);
}

void SynthGraph::setLoopPoints(double begin, double end)
{
    SynthCommand command;
    command.type = SynthCommandType::LOOP_POINTS;
    command.loopBegin = begin;
    command.loopEnd = end;
    commandBuffer.push(command);
}

void SynthGraph::setPos(double pos)
{
    SynthCommand command;
    command.type = SynthCommandType::POSITION;
    command.pos = pos;
    commandBuffer.push(command);
}

void SynthGraph::setSpeed(double speed)
{
    SynthCommand command;
    command.type = SynthCommandType::SPEED;
    command.speed = speed;
    commandBuffer.push(command);
}

void SynthGraph::setData(std::vector<double> *data, unsigned int height, unsigned int width)
{
    SynthCommand command;
    command.type = SynthCommandType::DATA;
    command.data = data;
    command.height = height;
    command.width = width;
    commandBuffer.push(command);
}

void SynthGraph::retrieveData()
{
    for(unsigned int i = 0; i < dataHeight; i++)
    {
        unsigned int idx = ((dataWidth * i) + currentIdx);
        currentData[i] = (*data)[idx];
    }
}

void SynthGraph::retrieveCommands()
{
    while(commandBuffer.pop(&currentCommand))
    {
        processCommand(currentCommand);
    }
}

void SynthGraph::processCommand(SynthCommand command)
{
    SynthCommandType type = command.type;

    switch (type) {
    case SynthCommandType::PAUSE:
    {
        processPause(command.paused);
    }
        break;

    case SynthCommandType::POSITION:
    {
        processSetPos(command.pos);
    }
        break;

    case SynthCommandType::SPEED:
    {
        speed = command.speed;
    }
        break;

    case SynthCommandType::LOOP:
    {
        looping = command.looping;
    }
        break;

    case SynthCommandType::LOOP_POINTS:
    {
        loopBegin = command.loopBegin;
        loopEnd = command.loopEnd;
    }
        break;
    case SynthCommandType::DATA:
    {
        processSetData(command.data, command.height, command.width);
    }
        break;


    default:
        break;
    }
}

double SynthGraph::getPos()
{
    return returnPos;
}

void SynthGraph::processPause(bool pause)
{
    if(paused != pause)
    {
        if(!pause)
        {
            dataStale = true;
        }
        paused = pause;
    }
}

void SynthGraph::processSetPos(double pos)
{
    unsigned int newIdx = (int)pos;
    if(currentIdx != newIdx)
    {
        dataStale = true;
        currentIdx = newIdx;
    }
    mu = (pos - currentIdx);
}

void SynthGraph::processSetData(std::vector<double> *inData, unsigned int height, unsigned int width)
{
    paused = true;
    data = inData;
    dataWidth = width;
    currentData.clear();
    currentIdx = 0;
    mu = 0.0;
    calculateReturnPos();

    if(dataHeight != height)
    {
        dataHeight = height;
        currentData.resize(dataHeight);
    }
}

void SynthGraph::calculateReturnPos()
{
    double pos = ((double)currentIdx + mu);
    returnPos.store(pos, std::memory_order_relaxed);
}

} //namespace son
