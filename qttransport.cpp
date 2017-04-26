#include "qttransport.h"

QtTransport::QtTransport(QObject *parent) : QObject(parent)
{

}

void QtTransport::setInterpolate(bool interpolate)
{
    transport.setInterpolate(interpolate);
}

QtSynthItem* QtTransport::createItem(ITEM type)
{
    SynthItem* item = NULL;
    QtSynthItem* qtItem = NULL;

    switch (type){
    case ITEM::OUT:
    {
        break;
    }
    case ITEM::OSCILLATOR:
    {
        item = transport.createItem((SynthItem::ITEM)type);
        qtItem = new QtOscillator(item);
        break;
    }
    case ITEM::AUDIFIER:
    {
        item = transport.createItem((SynthItem::ITEM)type);
        qtItem = new QtAudifier(item);
        break;
    }
    case ITEM::MODULATOR:
    {
        item = transport.createItem((SynthItem::ITEM)type);
        qtItem = new QtModulator(item);
        break;
    }
    default:
        break;
    }
    return qtItem;
}

float QtTransport::process()
{
    float s;
    s = transport.process();
    return s;
}

int QtTransport::graphSize()
{
    int size;
    size = transport.graphSize();
    return size;
}

void QtTransport::pause(bool pause)
{
    transport.pause(pause);
}

void QtTransport::setPos(double pos)
{
    transport.setPos(pos);
}

void QtTransport::setSpeed(double speed)
{
    transport.setSpeed(speed);
}

void QtTransport::setLooping(bool looping)
{
    transport.setLooping(looping);
}

void QtTransport::setLoopPoints(double begin, double end)
{
    transport.setLoopPoints(begin, end);
}

void QtTransport::setData(std::vector<double> *data, unsigned int height, unsigned int width)
{
    transport.setData(data, height, width);
}

double QtTransport::getPos()
{
    double pos;
    pos = transport.getPos();
    return pos;
}
