#include "qttransport.h"
#include "utility.h"
#include <QDebug>
#include <QString>

namespace sow {

QtTransport::QtTransport(QObject *parent) : QtSynthItem (parent)
{
    // Timer updates playhead position
    QTimer* posTimer = new QTimer(this);
    connect(posTimer, SIGNAL(timeout()), this, SLOT(updatePos()));
    posTimer->start(33);

    dataset_ = new Dataset;

    type_ = SowEnums::ITEM::TRANSPORT;
    paused_ = true;
    loop_ = false;
    loopBegin_ = 0.0;
    loopEnd_ = 0.0;
    dataStale_ = false;
    frameRate_ = 44100;
    currentIndex_ = 0;
    mu_ = 0.0;
    speed_ = 1;
    returnPos_ = 0.0;
    masterVolume_ = 1.0;
    interpolate_ = false;

    acceptedInputs_ = {
//        SowEnums::PARAMETER::INPUT
    };
}

/*
 Functions called from user thread
 */

void QtTransport::deleteItem(QtSynthItem *item)
{
    TransportCommand cmd;
    cmd.type = SowEnums::TRANSPORT_CMD::DELETE_ITEM;
    cmd.item = item;
    transportCommandBuffer_.push(cmd);
}

void QtTransport::onDatasetchanged(Dataset *dataset)
{
    DatasetCommand cmd;
    cmd.dataset = dataset;
    datasetCommandBuffer_.push(cmd);
}

void QtTransport::onPausechanged(bool pause)
{
    TransportCommand cmd;
    cmd.type = SowEnums::TRANSPORT_CMD::PAUSE;
    cmd.valueA = pause ? 1.0f : 0.0f;
    transportCommandBuffer_.push(cmd);
}

void QtTransport::onPoschanged(float pos)
{
    TransportCommand cmd;
    cmd.type = SowEnums::TRANSPORT_CMD::POS;
    cmd.valueA = pos;
    transportCommandBuffer_.push(cmd);
}

void QtTransport::onSpeedchanged(float speed)
{
    TransportCommand cmd;
    cmd.type = SowEnums::TRANSPORT_CMD::SPEED;
    cmd.valueA = speed;
    transportCommandBuffer_.push(cmd);
}

void QtTransport::onLoopingchanged(bool looping)
{
    TransportCommand cmd;
    cmd.type = SowEnums::TRANSPORT_CMD::LOOP;
    cmd.valueA = looping ? 1.0f : 0.0f;
    transportCommandBuffer_.push(cmd);
}

void QtTransport::onLoopPointsChanged(float begin, float end)
{
    TransportCommand cmd;
    cmd.type = SowEnums::TRANSPORT_CMD::LOOP_PTS;
    cmd.valueA = begin;
    cmd.valueB = end;
    transportCommandBuffer_.push(cmd);
}

void QtTransport::onInterpolateChanged(bool interpolate)
{
    TransportCommand cmd;
    cmd.type = SowEnums::TRANSPORT_CMD::INTERPOLATE;
    cmd.valueA = interpolate ? 1.0f : 0.0f;
    transportCommandBuffer_.push(cmd);
}

void QtTransport::subscribe(QtSynthItem *item)
{
    TransportCommand cmd;
    cmd.type = SowEnums::TRANSPORT_CMD::SUB;
    cmd.item = item;
    transportCommandBuffer_.push(cmd);
}

void QtTransport::unsubscribe(QtSynthItem *item)
{
    TransportCommand cmd;
    cmd.type = SowEnums::TRANSPORT_CMD::UNSUB;
    cmd.item = item;
    transportCommandBuffer_.push(cmd);
}

QtSynthItem* QtTransport::createItem(SowEnums::ITEM type)
{
    QtSynthItem* item;

    switch (type){
    case SowEnums::ITEM::OUT:
        item = this;
        break;
    case SowEnums::ITEM::OSCILLATOR:
        item = new QtOscillator(this);
        break;
//    case QtSynthItem::ITEM::AUDIFIER:
//        item = new Audifier();
//        break;
//    case QtSynthItem::ITEM::MODULATOR:
//        item = new Modulator();
//        break;
//    case QtSynthItem::ITEM::PANNER:
//        item = new Panner();
//        break;
//    case QtSynthItem::ITEM::ENVELOPE:
//        item = new Envelope();
//        break;
//    case QtSynthItem::ITEM::VOLUME:
//        item = new Volume();
//        break;
//    case QtSynthItem::ITEM::NOISE:
//        item = new Noise();
//        break;
//    case QtSynthItem::ITEM::EQUALIZER:
//        item = new Equalizer();
//        break;
    default:
        item = nullptr;
        break;
    }
//    item->setData(&current_data_column_, &dataset_->mins_, &dataset_->maxes_);
    return item;
}

float QtTransport::pos()
{
    return returnPos_;
}

/*
 Functions called from audio callback thread
 */

Frame QtTransport::process()
{
    Frame frame;
    bool stepping = false;

    if(paused_)
    {
        calculateReturnPosition();
        return frame;
    }

    // updating playheadPos
    if(mu_ >= 1.0)
    {
        mu_ -= 1.0;
        currentIndex_++;

        if((currentIndex_ + 1) > (dataset_->width_))
        {
            currentIndex_ = 0;
        }
        dataStale_ = true;
        stepping = true;
    }

    if(loop_ && (loopBegin_ != loopEnd_))
    {
        if(((double)currentIndex_ + mu_) > loopEnd_)
        {
            currentIndex_ = (int)loopBegin_;
            mu_ = (loopBegin_ - currentIndex_);
            dataStale_ = true;
        }
        else if(((double)currentIndex_ + mu_) < loopBegin_)
        {
            currentIndex_ = (int)loopBegin_;
            mu_ = (loopBegin_ - currentIndex_);
            dataStale_ = true;
        }
    }

    if(interpolate_)
    {
        dataStale_ = true;
    }

    if(dataStale_)
    {
        retrieveNextDataColumn();
        dataStale_ = false;
    }

    if(stepping)
    {
        step();
    }

    for (int i = 0; i < children_.size(); ++i)
    {
        QtSynthItem* item = children_[i];
        frame += item->process();
    }

    // advancing index
    calculateReturnPosition();
    mu_ += ((double)speed_ / frameRate_);

    return frame;// * master_volume_;
}

void QtTransport::controlProcess()
{
    // Do the usual for controlProcess
    QtSynthItem::controlProcess();
    // Trigger subscribed SynthItems to do the same
    for (int i = 0; i < subscribers_.size(); ++i)
    {
        QtSynthItem* item = subscribers_[i];
        item->controlProcess();
    }
    // Process TransportCommands
    TransportCommand cmd;
    while(transportCommandBuffer_.pop(&cmd)) {
        processTransportCommand(cmd);
    }
}

void QtTransport::processTransportCommand(TransportCommand cmd)
{

    switch (cmd.type) {
    case SowEnums::TRANSPORT_CMD::PAUSE:
        paused_ = (cmd.valueA == 0.0f) ? false : true;
        break;
    case SowEnums::TRANSPORT_CMD::POS:
        processSetPlaybackPosition(cmd.valueA);
        break;
    case SowEnums::TRANSPORT_CMD::SPEED:
        speed_ = static_cast<int>(cmd.valueA);
        break;
    case SowEnums::TRANSPORT_CMD::LOOP:
        loop_ = (cmd.valueA == 0.0f) ? false : true;
        break;
    case SowEnums::TRANSPORT_CMD::LOOP_PTS:
        loopBegin_ = cmd.valueA;
        loopEnd_ = cmd.valueB;
        break;
    case SowEnums::TRANSPORT_CMD::INTERPOLATE:
        interpolate_ = (cmd.valueA == 0.0f) ? false : true;
        break;
    case SowEnums::TRANSPORT_CMD::DELETE_ITEM:
        processDeleteItem(cmd.item);
        break;
    case SowEnums::TRANSPORT_CMD::SUB:
        processSubscribeItem(cmd.item);
        break;
    case SowEnums::TRANSPORT_CMD::UNSUB:
            subscribers_.removeAll(cmd.item);
        break;
    }
}

void QtTransport::processSubscribeItem(QtSynthItem *item)
{
    subscribers_.push_back(item);
    item->setData(&currentDataColumn_, &dataset_->mins_, &dataset_->maxes_);
}

void QtTransport::processUnsubscribeItem(QtSynthItem *item)
{
    subscribers_.removeAll(item);
}

void QtTransport::processDeleteItem(QtSynthItem *item)
{
    // Disconnect from control process calls
    processUnsubscribeItem(item);
    // Disconnect item from all parents/children
    item->disconnectAll();
    // Process the disconnectAll() command
    // buffered in preceeding line before del
    item->controlProcess();
    delete item;
}

void QtTransport::processDatasetCommand(DatasetCommand cmd)
{
    paused_ = true;
    dataset_ = cmd.dataset;
    currentDataColumn_.clear();
    currentIndex_ = 0;
    mu_ = 0.0;
    calculateReturnPosition();
    currentDataColumn_.resize(static_cast<int>(dataset_->height_));
}

void QtTransport::processSetPlaybackPosition(float pos)
{
    unsigned int newIdx = static_cast<unsigned int>(pos);
    if(currentIndex_ != newIdx)
    {
        dataStale_ = true;
        currentIndex_ = newIdx;
    }
    mu_ = (pos - currentIndex_);
}

void QtTransport::retrieveNextDataColumn()
{
    if(interpolate_)
    {
        unsigned int next_index = currentIndex_ + 1;
        if(next_index >= dataset_->width_)
        {
            next_index = 0;
        }
        currentDataColumn_ = interpolate(dataset_->get_column(currentIndex_), dataset_->get_column(next_index), mu_);
    }
    else {
        currentDataColumn_ = dataset_->get_column(currentIndex_);
    }
}

void QtTransport::calculateReturnPosition()
{
    // FIXME not on every callback
    double pos = ((double)currentIndex_ + mu_);
    returnPos_.store(pos, std::memory_order_relaxed);
}

QVector<double> QtTransport::interpolate(QVector<double> first, QVector<double> second, double mu)
{
    QVector<double> vec;
    if(first.size() != second.size())
    {
        return vec;
    }
    for(unsigned int i = 0; i < first.size(); i++)
    {
        double val_first = first[i];
        double val_second = second[i];
        double interpolated_val = ((1 - mu) * val_first) + (mu * val_second);
        vec.push_back(interpolated_val);
    }
    return vec;
}

void QtTransport::updatePos()
{
    float posVal = pos();
    emit posChanged(posVal);
}

} // Namespace sow.
