#include "transport.h"

namespace son {

Transport::Transport()
{
    paused = true;
    looping = false;
    loopBegin = 0.0;
    loopEnd = 0.0;
    dataStale = false;
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

    acceptedChildren = {
        SynthItem::PARAMETER::INPUT
    };
}

float Transport::process()
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

    for (unsigned int i = 0; i < children.size(); ++i) {
        SynthItem* item = children[i];
        s += item->process();
    }

    // advancing index
    calculateReturnPos();
    mu += (speed / sr);

    return s * masterVolume;
}

SynthItem* Transport::createItem(SynthItem::ITEM type)
{
    SynthItem* item;

    switch (type){
    case SynthItem::ITEM::TRANSPORT:
    {
        item = NULL;
        break;
    }
    case SynthItem::ITEM::OSCILLATOR:
    {
        item = new Oscillator();
        item->setData(&currentDataColumn, &minDataVals, &maxDataVals);
        break;
    }
    case SynthItem::ITEM::AUDIFIER:
    {
        item = new Audifier();
        item->setData(&currentDataColumn, &minDataVals, &maxDataVals);
        break;
    }
    case SynthItem::ITEM::MODULATOR:
    {
        item = new Modulator();
        item->setData(&currentDataColumn, &minDataVals, &maxDataVals);
        break;
    }
    default:
        item = NULL;
        break;
    }
    return item;
}

int Transport::graphSize()
{
    return children.size();
}

void Transport::pause(bool pause)
{
    SynthItemCommand command;
    command.type = COMMAND::PAUSE;
    command.boolVal = pause;
    commandBuffer.push(command);
}

void Transport::setLooping(bool looping)
{
    SynthItemCommand command;
    command.type = COMMAND::LOOP;
    command.boolVal = looping;
    commandBuffer.push(command);
}

void Transport::setLoopPoints(double begin, double end)
{
    SynthItemCommand command;
    command.type = COMMAND::LOOP_POINTS;
    command.doubles.push_back(begin);
    command.doubles.push_back(end);
    commandBuffer.push(command);
}

void Transport::setPos(double pos)
{
    SynthItemCommand command;
    command.type = COMMAND::POSITION;
    command.doubles.push_back(pos);
    commandBuffer.push(command);
}

void Transport::setSpeed(double speed)
{
    SynthItemCommand command;
    command.type = COMMAND::SPEED;
    command.doubles.push_back(speed);
    commandBuffer.push(command);
}

void Transport::setData(std::vector<double> *data, unsigned int height, unsigned int width)
{
    SynthItemCommand command;
    command.type = COMMAND::DATA;
    command.data = data;
    command.ints.push_back(height);
    command.ints.push_back(width);
    commandBuffer.push(command);
}

void Transport::setInterpolate(bool interpolate)
{
    SynthItemCommand command;
    command.type = COMMAND::INTERPOLATE;
    command.boolVal = interpolate;
    commandBuffer.push(command);
}

void Transport::retrieveData()
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
            currentDataColumn[i] = ((1 - mu) * val) + (mu * valNext);
        }
    }
    else {
        for(unsigned int i = 0; i < dataHeight; i++)
        {
            unsigned int idx = ((dataWidth * i) + currentIdx);
            currentDataColumn[i] = (*data)[idx];
        }
    }
}

void Transport::retrieveCommands()
{
    while(commandBuffer.pop(&currentCommand))
    {
        processCommand(currentCommand);
    }
}

void Transport::processCommand(SynthItemCommand command)
{
    COMMAND type = command.type;

    switch (type) {
    case COMMAND::DATA:
        processSetDataset(command.data, command.ints[0], command.ints[1]);
        break;
    case COMMAND::PAUSE:
        processPause(command.boolVal);
        break;
    case COMMAND::POSITION:
        processSetPos(command.doubles[0]);
        break;
    case COMMAND::SPEED:
        speed = command.doubles[0];
        break;
    case COMMAND::LOOP:
        looping = command.boolVal;
        break;
    case COMMAND::LOOP_POINTS:
        loopBegin = command.doubles[0];
        loopEnd = command.doubles[1];
        break;
    case COMMAND::INTERPOLATE:
        processSetInterpolate(command.boolVal);
        break;
    default:
        SynthItem::processCommand(command);
        break;
    }
}

void Transport::processAddChild(SynthItem *child, SynthItem::PARAMETER parameter)
{
    if(std::find(children.begin(), children.end(), child) != children.end()) {
        return;
    } else {
        children.push_back(child);
    }
}

void Transport::processRemoveChild(SynthItem *child)
{
    amods.erase(std::remove(amods.begin(), amods.end(), child), amods.end());
}

void Transport::processDeleteItem()
{
    delete this;
}

double Transport::getPos()
{
    return returnPos;
}

void Transport::processPause(bool pause)
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

void Transport::processSetPos(double pos)
{
    unsigned int newIdx = (int)pos;
    if(currentIdx != newIdx)
    {
        dataStale = true;
        currentIdx = newIdx;
    }
    mu = (pos - currentIdx);
}

void Transport::processSetDataset(std::vector<double> *data, int height, int width)
{
    currentIdx = 0;
    mu = 0.0;
    calculateReturnPos();
    dataWidth = width;
    dataHeight = height;
    currentDataColumn.clear();
    currentDataColumn.resize(dataHeight);
    this->data = data;
    calculateMinMax();
}

void Transport::processSetInterpolate(bool interpolate)
{
    this->interpolate = interpolate;
}

void Transport::calculateReturnPos()
{
    // FIXME not on every callback
    double pos = ((double)currentIdx + mu);
    returnPos.store(pos, std::memory_order_relaxed);
}

void Transport::calculateMinMax()
{
    double min;
    double max;
    minDataVals.clear();
    maxDataVals.clear();
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
        minDataVals.push_back(min);
        maxDataVals.push_back(max);
    }
}

} //namespace son
