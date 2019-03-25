#include <QDebug>
#include <QString>
#include "constants.h"
#include "transport.h"
#include "utility.h"

namespace sow {

Transport::Transport(QObject *parent) : SynthItem (parent)
{  
    type_ = ENUMS::ITEM_TYPE::TRANSPORT;
    acceptedInputs_ = {
        ENUMS::OUTPUT_TYPE::AUDIO,
        ENUMS::OUTPUT_TYPE::AM
    };

    // Timer updates playhead position
    QTimer* posTimer = new QTimer(this);
    connect(posTimer, SIGNAL(timeout()), this, SLOT(updatePos()));
    posTimer->start(33);

    pause_ = true;
    loop_ = false;
    loopBegin_ = 0.0f;
    loopEnd_ = 0.0f;
    dataStale_ = false;
    frameRate_ = constants::SR;
    currentIndex_ = 0;
    mu_ = 0.0f;
    speed_ = 1;
    returnPos_ = 0.0f;
    masterVolume_ = 1.0f;
    interpolate_ = false;
}

/*
 Functions called from user thread
 */

void Transport::deleteItem(SynthItem *item)
{
    TransportCommand cmd;
    cmd.type = ENUMS::TRANSPORT_CMD::DELETE_ITEM;
    cmd.item = item;
    transportCommandBuffer_.push(cmd);
}


void Transport::onImportDataset(QString file)
{
    if (filepath_ != file) {
        fileMutex_.lock();
        filepath_ = file;
        fileMutex_.unlock();
    }
    TransportCommand cmd;
    cmd.type = ENUMS::TRANSPORT_CMD::IMPORT_DATASET;
    transportCommandBuffer_.push(cmd);
}

void Transport::onPausechanged(bool pause)
{
    TransportCommand cmd;
    cmd.type = ENUMS::TRANSPORT_CMD::PAUSE;
    cmd.valueA = pause ? 1.0f : 0.0f;
    transportCommandBuffer_.push(cmd);
}

void Transport::onPoschanged(float pos)
{
    TransportCommand cmd;
    cmd.type = ENUMS::TRANSPORT_CMD::POS;
    cmd.valueA = pos;
    transportCommandBuffer_.push(cmd);
}

void Transport::onSpeedchanged(float speed)
{
    TransportCommand cmd;
    cmd.type = ENUMS::TRANSPORT_CMD::SPEED;
    cmd.valueA = speed;
    transportCommandBuffer_.push(cmd);
}

void Transport::onLoopingchanged(bool looping)
{
    TransportCommand cmd;
    cmd.type = ENUMS::TRANSPORT_CMD::LOOP;
    cmd.valueA = looping ? 1.0f : 0.0f;
    transportCommandBuffer_.push(cmd);
}

void Transport::onLoopPointsChanged(float begin, float end)
{
    TransportCommand cmd;
    cmd.type = ENUMS::TRANSPORT_CMD::LOOP_PTS;
    cmd.valueA = begin;
    cmd.valueB = end;
    transportCommandBuffer_.push(cmd);
}

void Transport::onInterpolateChanged(bool interpolate)
{
    TransportCommand cmd;
    cmd.type = ENUMS::TRANSPORT_CMD::INTERPOLATE;
    cmd.valueA = interpolate ? 1.0f : 0.0f;
    transportCommandBuffer_.push(cmd);
}

void Transport::subscribe(SynthItem *item)
{
    TransportCommand cmd;
    cmd.type = ENUMS::TRANSPORT_CMD::SUB;
    cmd.item = item;
    transportCommandBuffer_.push(cmd);
}

void Transport::unsubscribe(SynthItem *item)
{
    TransportCommand cmd;
    cmd.type = ENUMS::TRANSPORT_CMD::UNSUB;
    cmd.item = item;
    transportCommandBuffer_.push(cmd);
}

SynthItem* Transport::createItem(ENUMS::ITEM_TYPE type)
{
    SynthItem* item = nullptr;

    qDebug() << type;

    switch (type){
    case ENUMS::ITEM_TYPE::NONE:
        break;
    case ENUMS::ITEM_TYPE::OSCILLATOR:
        item = new Oscillator(this);
        processSubscribeItem(item);
        break;
    case ENUMS::ITEM_TYPE::AUDIFIER:
        item = new Audifier(this);
        processSubscribeItem(item);
        break;
    case ENUMS::ITEM_TYPE::AMOD:
        item = new Amod(this);
        processSubscribeItem(item);
        break;
    case ENUMS::ITEM_TYPE::FMOD:
        item = new Fmod(this);
        processSubscribeItem(item);
        break;
    case ENUMS::ITEM_TYPE::PANNER:
        item = new Panner(this);
        processSubscribeItem(item);
        break;
    case ENUMS::ITEM_TYPE::ENVELOPE:
        //        item = new Envelope();
        break;
    case ENUMS::ITEM_TYPE::VOLUME:
        //        item = new Volume();
        break;
    case ENUMS::ITEM_TYPE::NOISE_GEN:
        //        item = new Noise();
        break;
    case ENUMS::ITEM_TYPE::EQUALIZER:
        //        item = new Equalizer();
        break;
    case ENUMS::ITEM_TYPE::TRANSPORT:
        item = this;
        break;
    }
    return item;
}

float Transport::pos()
{
    return returnPos_;
}

/*
 Functions called from audio callback thread
 */

Frame Transport::process()
{
    Frame frame;
    bool stepping = false;

    if(pause_)
    {
        calculateReturnPosition();
        return frame;
    }

    // updating playheadPos
    if(mu_ >= 1.0)
    {
        mu_ -= 1.0;
        currentIndex_++;

        if((currentIndex_ + 1) > (dataset_.rows()))
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

    if(dataStale_ && dataset_.hasData())
    {
        refreshCurrentData();
        dataStale_ = false;
    }

    if(stepping)
    {
        step();
    }

    for (int i = 0; i < children_.size(); ++i)
    {
        SynthItem* item = children_[i];
        frame += item->process();
    }

    // advancing index
    calculateReturnPosition();
    mu_ += static_cast<float>(speed_) / frameRate_;

    return frame;// * master_volume_;
}

void Transport::controlProcess()
{
    // Process TransportCommands
    TransportCommand cmd;
    while(transportCommandBuffer_.pop(&cmd)) {
        processTransportCommand(cmd);
    }
    // Do the usual for controlProcess
    SynthItem::controlProcess();
    // Trigger subscribed SynthItems to do the same
    for (int i = 0; i < subscribers_.size(); ++i)
    {
        SynthItem* item = subscribers_[i];
        item->controlProcess();
    }
}

void Transport::processTransportCommand(TransportCommand cmd)
{

    switch (cmd.type) {
    case ENUMS::TRANSPORT_CMD::PAUSE:
        pause_ = (cmd.valueA == 0.0f) ? false : true;
        break;
    case ENUMS::TRANSPORT_CMD::POS:
        processSetPlaybackPosition(cmd.valueA);
        break;
    case ENUMS::TRANSPORT_CMD::SPEED:
        speed_ = static_cast<int>(cmd.valueA);
        break;
    case ENUMS::TRANSPORT_CMD::LOOP:
        loop_ = (cmd.valueA == 0.0f) ? false : true;
        break;
    case ENUMS::TRANSPORT_CMD::LOOP_PTS:
        loopBegin_ = cmd.valueA;
        loopEnd_ = cmd.valueB;
        break;
    case ENUMS::TRANSPORT_CMD::INTERPOLATE:
        interpolate_ = (cmd.valueA == 0.0f) ? false : true;
        break;
    case ENUMS::TRANSPORT_CMD::DELETE_ITEM:
        processDeleteItem(cmd.item);
        break;
    case ENUMS::TRANSPORT_CMD::SUB:
        processSubscribeItem(cmd.item);
        break;
    case ENUMS::TRANSPORT_CMD::UNSUB:
        utility::removeAll(cmd.item, subscribers_);
        break;
    case ENUMS::TRANSPORT_CMD::IMPORT_DATASET:
        processImportDataset();
        break;
    }
}

void Transport::processSubscribeItem(SynthItem *item)
{
    utility::insertUnique(item, subscribers_);
    item->setData(&dataset_, &currentData_);
}

void Transport::processUnsubscribeItem(SynthItem *item)
{
    utility::removeAll(item, subscribers_);
}

void Transport::processDeleteItem(SynthItem *item)
{
    // Disconnect from control process calls
    processUnsubscribeItem(item);
    // Disconnect item from all parents/children
    item->disconnectAll();
    // Process the disconnectAll() command
    // buffered in preceeding line before del
    item->controlProcess();
    if(item != this) {
        delete item;
    }
}

void Transport::processImportDataset()
{
    pause_ = true;
    currentData_.clear();
    currentIndex_ = 0;
    mu_ = 0.0f;
    calculateReturnPosition();

    FileReader reader;
    fileMutex_.lock();
    reader.readCSV(filepath_, &dataset_);
    currentData_.resize(dataset_.rows());
    currentData_ = dataset_.getRow(currentIndex_);
    fileMutex_.unlock();
    emit datasetImported(&dataset_);
}


void Transport::processSetPlaybackPosition(float pos)
{
    int newIdx = static_cast<int>(pos);
    if(currentIndex_ != newIdx)
    {
        dataStale_ = true;
        currentIndex_ = newIdx;
    }
    mu_ = (pos - currentIndex_);
}

void Transport::refreshCurrentData()
{
    if(interpolate_)
    {
        int next_index = currentIndex_ + 1;
        if(next_index >= dataset_.rows())
        {
            next_index = 0;
        }
        currentData_ = interpolate(dataset_.getRow(currentIndex_), dataset_.getRow(next_index), mu_);
    }
    else {
        currentData_ = dataset_.getRow(currentIndex_);
    }
}

void Transport::calculateReturnPosition()
{
    // FIXME not on every callback
    double pos = ((double)currentIndex_ + mu_);
    returnPos_.store(pos, std::memory_order_relaxed);
}

std::vector<float> Transport::interpolate(std::vector<float> first, std::vector<float> second, float mu)
{
    std::vector<float> vec;
    if(first.size() != second.size())
    {
        return vec;
    }
    for(int i = 0; i < first.size(); i++)
    {
        float val_first = first[i];
        float val_second = second[i];
        float interpolated_val = ((1 - mu) * val_first) + (mu * val_second);
        vec.push_back(interpolated_val);
    }
    return vec;
}

void Transport::updatePos()
{
    float posVal = pos();
    emit posChanged(posVal);
}

} // Namespace sow.
