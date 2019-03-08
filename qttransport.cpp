#include "qttransport.h"

using namespace sow;

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

QtSynthItem* QtTransport::createItem(QT_ITEM type)
{
    SynthItem* item = NULL;
    QtSynthItem* qtItem = NULL;

    switch (type){
    case QT_ITEM::OUT:
        qtItem = this;
        break;
    case QT_ITEM::OSCILLATOR:
        item = transport_.create_item((SynthItem::ITEM)type);
        qtItem = new QtOscillator(dynamic_cast<Oscillator*>(item));
        subscribeItem(qtItem);
        break;
//    case QT_ITEM::AUDIFIER:
//        item = transport_.create_item((SynthItem::ITEM)type);
//        qtItem = new QtAudifier(dynamic_cast<Audifier*>(item));
//        subscribeItem(qtItem);
//        break;
//    case QT_ITEM::MODULATOR:
//        item = transport_.create_item((SynthItem::ITEM)type);
//        qtItem = new QtModulator(dynamic_cast<Modulator*>(item));
//        subscribeItem(qtItem);
//        break;
//    case QT_ITEM::PANNER:
//        item = transport_.create_item((SynthItem::ITEM)type);
//        qtItem = new QtPanner(dynamic_cast<Panner*>(item));
//        subscribeItem(qtItem);
//        break;
//    case QT_ITEM::ENVELOPE:
//        item = transport_.create_item((SynthItem::ITEM)type);
//        qtItem = new QtEnvelope(dynamic_cast<Envelope*>(item));
//        subscribeItem(qtItem);
//        break;
//    case QT_ITEM::VOLUME:
//        item = transport_.create_item((SynthItem::ITEM)type);
//        qtItem = new QtVolume(dynamic_cast<Volume*>(item));
//        subscribeItem(qtItem);
//        break;
//    case QT_ITEM::NOISE:
//        item = transport_.create_item((SynthItem::ITEM)type);
//        qtItem = new QtNoise(dynamic_cast<Noise*>(item));
//        subscribeItem(qtItem);
//        break;
//    case QT_ITEM::EQUALIZER:
//        item = transport_.create_item((SynthItem::ITEM)type);
//        qtItem = new QtEqualizer(dynamic_cast<Equalizer*>(item));
//        subscribeItem(qtItem);
//        break;
    default:
        break;
    }
    return qtItem;
}

void QtTransport::deleteSelf()
{
    transport_.delete_self();
}

void QtTransport::addParent(QtSynthItem *parent)
{
    transport_.add_parent(parent->implementation());
}

void QtTransport::removeParent(QtSynthItem *parent)
{
    transport_.remove_parent(parent->implementation());
}

bool QtTransport::addChild(QtSynthItem *child, QtSynthItem::QT_PARAMETER param)
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

void QtTransport::deleteItem(QtSynthItem *item)
{
    transport_.delete_item(item->implementation());
}

void QtTransport::subscribeItem(QtSynthItem *item)
{
    transport_.subscribe_item(item->implementation());
}

void QtTransport::on_datasetChanged(Dataset* dataset)
{
    transport_.pause(true);
    transport_.set_dataset(dataset);
}

void QtTransport::on_pausedChanged(bool pause)
{
    transport_.pause(pause);
}

void QtTransport::on_posChanged(double pos)
{
    transport_.set_playback_position(pos);
}

void QtTransport::on_speedChanged(int speed)
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
