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
    dynamic_cast<Transport*>(synthItem)->set_interpolate(interpolate);
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
        item = dynamic_cast<Transport*>(synthItem)->create_item((SynthItem::ITEM)type);
        qtItem = new QtOscillator(item);
        break;
    }
    case ITEM::AUDIFIER:
    {
        item = dynamic_cast<Transport*>(synthItem)->create_item((SynthItem::ITEM)type);
        qtItem = new QtAudifier(item);
        break;
    }
    case ITEM::MODULATOR:
    {
        item = dynamic_cast<Transport*>(synthItem)->create_item((SynthItem::ITEM)type);
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

void QtTransport::on_pausedChanged(bool pause)
{
    dynamic_cast<Transport*>(synthItem)->pause(pause);
}

void QtTransport::on_posChanged(double pos)
{
    dynamic_cast<Transport*>(synthItem)->set_playback_position(pos);
}

void QtTransport::on_speedChanged(double speed)
{
    dynamic_cast<Transport*>(synthItem)->set_speed(speed);
}

void QtTransport::on_loopingChanged(bool looping)
{
    dynamic_cast<Transport*>(synthItem)->set_looping(looping);
}

void QtTransport::on_loopPointsChanged(double begin, double end)
{
    dynamic_cast<Transport*>(synthItem)->set_loop_points(begin, end);
}

void QtTransport::on_dataChanged(std::vector<double> *data, unsigned int height, unsigned int width)
{
    Transport* t = dynamic_cast<Transport*>(synthItem);
    t->pause(true);
    t->set_dataset(data, height, width);
}

double QtTransport::getPos()
{
    double pos;
    pos = dynamic_cast<Transport*>(synthItem)->get_playback_position();
    return pos;
}

void QtTransport::updatePos()
{
    double pos = dynamic_cast<Transport*>(synthItem)->get_playback_position();
    emit posChanged(pos);
}
