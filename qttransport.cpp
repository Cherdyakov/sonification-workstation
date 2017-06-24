#include "qttransport.h"

using namespace son;

QtTransport::QtTransport(QObject *parent) : QtSynthItem(parent)
{
    // for refreshing the playhead position
    QTimer* posTimer = new QTimer(this);
    connect(posTimer, SIGNAL(timeout()), this, SLOT(updatePos()));
    posTimer->start(33);
}

SynthItem *QtTransport::implementation()
{
    return &transport_;
}

QtSynthItem* QtTransport::createItem(ITEM type)
{
    SynthItem* item = NULL;
    QtSynthItem* qtItem = NULL;

    switch (type){
    case ITEM::OUT:
        qtItem = this;
        break;
    case ITEM::OSCILLATOR:
        item = transport_.create_item((SynthItem::ITEM)type);
        qtItem = new QtOscillator(dynamic_cast<Oscillator*>(item));
        break;
    case ITEM::AUDIFIER:
        item = transport_.create_item((SynthItem::ITEM)type);
        qtItem = new QtAudifier(dynamic_cast<Audifier*>(item));
        break;
    case ITEM::MODULATOR:
        item = transport_.create_item((SynthItem::ITEM)type);
        qtItem = new QtModulator(dynamic_cast<Modulator*>(item));
        break;
    case ITEM::PANNER:
        item = transport_.create_item((SynthItem::ITEM)type);
        qtItem = new QtPanner(dynamic_cast<Panner*>(item));
        break;
    case ITEM::ENVELOPE:
        item = transport_.create_item((SynthItem::ITEM)type);
        qtItem = new QtEnvelope(dynamic_cast<Envelope*>(item));
        break;
    case ITEM::VOLUME:
        item = transport_.create_item((SynthItem::ITEM)type);
        qtItem = new QtVolume(dynamic_cast<Volume*>(item));
        break;
    default:
        break;
    }
    return qtItem;
}

void QtTransport::deleteItem()
{
    transport_.delete_item();
}

void QtTransport::addParent(QtSynthItem *parent)
{
    transport_.add_parent(parent->implementation());
}

void QtTransport::removeParent(QtSynthItem *parent)
{
    transport_.remove_parent(parent->implementation());
}

bool QtTransport::addChild(QtSynthItem *child, QtSynthItem::PARAMETER param)
{
    return transport_.add_child(child->implementation(), (SynthItem::PARAMETER)param);
}

void QtTransport::removeChild(QtSynthItem *child)
{
    transport_.remove_child(child->implementation());
}

void QtTransport::mute(bool mute)
{
    transport_.mute(mute);
}

void QtTransport::on_dataChanged(std::vector<double> *data, unsigned int height, unsigned int width)
{
    transport_.pause(true);
    transport_.set_dataset(data, height, width);
}

void QtTransport::on_pausedChanged(bool pause)
{
    transport_.pause(pause);
}

void QtTransport::on_posChanged(double pos)
{
    transport_.set_playback_position(pos);
}

void QtTransport::on_speedChanged(double speed)
{
    transport_.set_speed(speed);
}

void QtTransport::on_loopingChanged(bool looping)
{
    transport_.set_looping(looping);
}

void QtTransport::on_loopPointsChanged(double begin, double end)
{
    transport_.set_loop_points(begin, end);
}

void QtTransport::on_interpolateChanged(bool interpolate)
{
    transport_.set_interpolate(interpolate);
}

double QtTransport::getPos()
{
    double pos;
    pos = transport_.get_playback_position();
    return pos;
}

void QtTransport::updatePos()
{
    double pos = transport_.get_playback_position();
    emit posChanged(pos);
}
