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
    interpolate = false;

    acceptedChildTypes = {
        SynthItem::ITEM_CHILD_TYPE::INPUT
    };
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

    if(interpolate)
    {
        dataStale = true;
    }

    if(dataStale)
    {
        retrieveData();
        dataStale = false;
    }

    std::vector<SynthItem*>::const_iterator i;

    for (unsigned int i = 0; i < graphRoot.size(); ++i) {
        SynthItem* item = graphRoot[i];
        s += item->process();
    }

    // advancing index
    calculateReturnPos();
    mu += (speed / sr);

    return s * masterVolume;
}

SynthItem* SynthGraph::createItem(SynthItem::ITEM_TYPE type)
{
    SynthItem* item;

    switch (type){
    case SynthItem::ITEM_TYPE::OUT:
    {
        item = NULL;
        break;
    }
    case SynthItem::ITEM_TYPE::OSCILLATOR:
    {
        item = new Oscillator();
        item->setDataItem(&currentData, &mins, &maxes);
        break;
    }
    case SynthItem::ITEM_TYPE::AUDIFIER:
    {
        item = new Audifier();
        item->setDataItem(&currentData, &mins, &maxes);
        break;
    }
    case SynthItem::ITEM_TYPE::MODULATOR:
    {
        item = new Modulator();
        item->setDataItem(&currentData, &mins, &maxes);
        break;
    }
    default:
        item = NULL;
        break;
    }
    return item;
}

bool SynthGraph::addToRoot(SynthItem *child)
{
    if(!verifyChildType(child->getChildType()))
    {
        return false;
    }
    if(std::find(graphRoot.begin(), graphRoot.end(), child) != graphRoot.end()) {
        return false;
    }
    graphRoot.push_back(child);
    return true;
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
    SynthGraphCommand command;
    command.type = GRAPH_COMMAND_TYPE::PAUSE;
    command.boolVal = pause;
    commandBuffer.push(command);
}

void SynthGraph::setLooping(bool looping)
{
    SynthGraphCommand command;
    command.type = GRAPH_COMMAND_TYPE::LOOP;
    command.boolVal = looping;
    commandBuffer.push(command);
}

void SynthGraph::setLoopPoints(double begin, double end)
{
    SynthGraphCommand command;
    command.type = GRAPH_COMMAND_TYPE::LOOP_POINTS;
    command.doubleVal = begin;
    command.doubleVal2 = end;
    commandBuffer.push(command);
}

void SynthGraph::setPos(double pos)
{
    SynthGraphCommand command;
    command.type = GRAPH_COMMAND_TYPE::POSITION;
    command.doubleVal = pos;
    commandBuffer.push(command);
}

void SynthGraph::setSpeed(double speed)
{
    SynthGraphCommand command;
    command.type = GRAPH_COMMAND_TYPE::SPEED;
    command.doubleVal = speed;
    commandBuffer.push(command);
}

void SynthGraph::setData(std::vector<double> *data, unsigned int height, unsigned int width)
{
    SynthGraphCommand command;
    command.type = GRAPH_COMMAND_TYPE::DATA;
    command.data = data;
    command.height = height;
    command.width = width;
    commandBuffer.push(command);
}

void SynthGraph::setInterpolate(bool interpolate)
{
    SynthGraphCommand command;
    command.type = GRAPH_COMMAND_TYPE::INTERPOLATE;
    command.boolVal = interpolate;
    commandBuffer.push(command);
}

void SynthGraph::retrieveData()
{
    if(interpolate)
    {
        for(unsigned int i = 0; i < dataHeight; i++)
        {
            unsigned int idx = ((dataWidth * i) + currentIdx);
            unsigned int nextIdx = idx + 1;
            if(nextIdx > (dataWidth * i) + (dataWidth - 1)) {
                nextIdx -= dataWidth;
            }
            double val = (*data)[idx];
            double valNext = (*data)[nextIdx];
            currentData[i] = ((1 - mu) * val) + (mu * valNext);
        }
    }
    else {
        for(unsigned int i = 0; i < dataHeight; i++)
        {
            unsigned int idx = ((dataWidth * i) + currentIdx);
            currentData[i] = (*data)[idx];
        }
    }
}

void SynthGraph::retrieveCommands()
{
    while(commandBuffer.pop(&currentCommand))
    {
        processCommand(currentCommand);
    }
}

void SynthGraph::processCommand(SynthGraphCommand command)
{
    GRAPH_COMMAND_TYPE type = command.type;

    switch (type) {
    case GRAPH_COMMAND_TYPE::PAUSE:
    {
        processPause(command.boolVal);
        break;
    }
    case GRAPH_COMMAND_TYPE::POSITION:
    {
        processSetPos(command.doubleVal);
        break;
    }
    case GRAPH_COMMAND_TYPE::SPEED:
    {
        speed = command.doubleVal;
        break;
    }
    case GRAPH_COMMAND_TYPE::LOOP:
    {
        looping = command.boolVal;
        break;
    }
    case GRAPH_COMMAND_TYPE::LOOP_POINTS:
    {
        loopBegin = command.doubleVal;
        loopEnd = command.doubleVal2;
        break;
    }
    case GRAPH_COMMAND_TYPE::DATA:
    {
        processSetData(command.data, command.height, command.width);
        break;
    }
    case GRAPH_COMMAND_TYPE::INTERPOLATE:
    {
        processSetInterpolate(command.boolVal);
    }
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

void SynthGraph::processSetData(std::vector<double> *data, unsigned int height, unsigned int width)
{
    paused = true;
    this->data = data;
    dataWidth = width;
    currentData.clear();
    currentIdx = 0;
    mu = 0.0;
    calculateReturnPos();
    dataHeight = height;
    currentData.resize(dataHeight);
    calculateMinMax();
}

void SynthGraph::processSetInterpolate(bool interpolate)
{
    this->interpolate = interpolate;
}

void SynthGraph::calculateReturnPos()
{
    // FIXME not on every callback
    double pos = ((double)currentIdx + mu);
    returnPos.store(pos, std::memory_order_relaxed);
}

void SynthGraph::calculateMinMax()
{
    double min;
    double max;
    mins.clear();
    maxes.clear();
    for(unsigned int i = 0; i < dataHeight; i++)
    {
        for(unsigned int j = 0; j < dataWidth; j++)
        {
            unsigned int idx = i * dataWidth + j;
            double value = data->at(idx);
            if(j == 0)
            {
                min = max = value;
            }
            else if(value < min)
            {
                min = value;
            }
            else if(value > max)
            {
                max = value;
            }
        }
        mins.push_back(min);
        maxes.push_back(max);
    }
}

bool SynthGraph::verifyChildType(SynthItem::ITEM_CHILD_TYPE childType)
{
    if(std::find(acceptedChildTypes.begin(), acceptedChildTypes.end(), childType) == acceptedChildTypes.end())
    {
        return false;
    }
    return true;
}

} //namespace son
