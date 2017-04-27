#include "qttransport.h"

QtTransport::QtTransport(SynthItem *item, QObject *parent) : QtSynthItem(parent)
{
    synthItem = item;
    // for refreshing the playhead position
    QTimer* posTimer = new QTimer(this);
    connect(posTimer, SIGNAL(timeout()), this, SLOT(updatePos()));
    posTimer->start(33);
}

void QtTransport::on_interpolateChanged(bool interpolate)
{
    dynamic_cast<Transport*>(synthItem)->setInterpolate(interpolate);
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
        item = dynamic_cast<Transport*>(synthItem)->createItem((SynthItem::ITEM)type);
        qtItem = new QtOscillator(item);
        break;
    }
    case ITEM::AUDIFIER:
    {
        item = dynamic_cast<Transport*>(synthItem)->createItem((SynthItem::ITEM)type);
        qtItem = new QtAudifier(item);
        break;
    }
    case ITEM::MODULATOR:
    {
        item = dynamic_cast<Transport*>(synthItem)->createItem((SynthItem::ITEM)type);
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
    s = dynamic_cast<Transport*>(synthItem)->process();
    return s;
}

int QtTransport::graphSize()
{
    int size;
    size = dynamic_cast<Transport*>(synthItem)->graphSize();
    return size;
}

void QtTransport::on_pauseChanged(bool pause)
{
    dynamic_cast<Transport*>(synthItem)->pause(pause);
}

void QtTransport::on_posChanged(double pos)
{
    dynamic_cast<Transport*>(synthItem)->setPos(pos);
}

void QtTransport::on_speedChanged(double speed)
{
    dynamic_cast<Transport*>(synthItem)->setSpeed(speed);
}

void QtTransport::on_loopingChanged(bool looping)
{
    dynamic_cast<Transport*>(synthItem)->setLooping(looping);
}

void QtTransport::on_loopPointsChanged(double begin, double end)
{
    dynamic_cast<Transport*>(synthItem)->setLoopPoints(begin, end);
}

void QtTransport::on_dataChanged(std::vector<double> *data, unsigned int height, unsigned int width)
{
    dynamic_cast<Transport*>(synthItem)->setData(data, height, width);
}

double QtTransport::getPos()
{
    double pos;
    pos = dynamic_cast<Transport*>(synthItem)->getPos();
    return pos;
}

void QtTransport::updatePos()
{
    double pos = dynamic_cast<Transport*>(synthItem)->getPos();
    emit posChanged(pos);
}
