#include <QDebug>
#include <QString>
#include "constants.h"
#include "transport.h"
#include "utility.h"

namespace sow {

Transport::Transport(QObject *parent, Dataset *dataset, DataProcessorController *dataProcessorController) : SynthItem (parent)
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

    dataProcessorController_ = dataProcessorController;
    dataset_ = dataset;
    pause_ = true;
    record_ = false;
    loop_ = false;
    loopBegin_ = 0.0f;
    loopEnd_ = 0.0f;
    dataStale_ = false;
    frameRate_ = constants::SR;
    currentIndex_ = 0;
    mu_ = 0.0f;
    speed_ = 1;
    returnPos_ = 0.0f;
    masterVolumeTarget_ = masterVolume_ = 1.0f;
    importingDataset_ = false;
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


void Transport::onImportDataset(bool importing)
{
    TransportCommand cmd;
    cmd.type = ENUMS::TRANSPORT_CMD::IMPORT_DATASET;
    cmd.valueA = importing ? 1.0f : 0.0f;
    transportCommandBuffer_.push(cmd);
}

void Transport::onPauseChanged(bool pause)
{
    TransportCommand cmd;
    cmd.type = ENUMS::TRANSPORT_CMD::PAUSE;
    cmd.valueA = pause ? 1.0f : 0.0f;
    transportCommandBuffer_.push(cmd);
}

void Transport::onRecordStart(QString path)
{
    recorder_.Start(path);
    TransportCommand cmd;
    cmd.type = ENUMS::TRANSPORT_CMD::RECORD;
    cmd.valueA = 1.0f;
    transportCommandBuffer_.push(cmd);
}

void Transport::onRecordStop()
{
    recorder_.Stop();
    TransportCommand cmd;
    cmd.type = ENUMS::TRANSPORT_CMD::RECORD;
    cmd.valueA = 0.0f;
    transportCommandBuffer_.push(cmd);
}

void Transport::onPosChanged(float pos)
{
    TransportCommand cmd;
    cmd.type = ENUMS::TRANSPORT_CMD::POS;
    cmd.valueA = pos;
    transportCommandBuffer_.push(cmd);
}

void Transport::onSpeedChanged(float speed)
{
    TransportCommand cmd;
    cmd.type = ENUMS::TRANSPORT_CMD::SPEED;
    cmd.valueA = speed;
    transportCommandBuffer_.push(cmd);
}

void Transport::onLoopingChanged(bool looping)
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

void Transport::onMuteChanged(bool mute)
{
    TransportCommand cmd;
    cmd.type = ENUMS::TRANSPORT_CMD::MUTE;
    cmd.valueA = mute ? 1.0f : 0.0f;
    transportCommandBuffer_.push(cmd);
}

void Transport::onMasterVolumeChanged(float vol)
{
    TransportCommand cmd;
    cmd.type = ENUMS::TRANSPORT_CMD::VOLUME;
    cmd.valueA = vol;
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
        item = new Envelope(this);
        processSubscribeItem(item);
        break;
    case ENUMS::ITEM_TYPE::VOLUME:
        item = new Volume(this);
        processSubscribeItem(item);
        break;
    case ENUMS::ITEM_TYPE::NOISE_GEN:
        item = new Noise(this);
        processSubscribeItem(item);
        break;
    case ENUMS::ITEM_TYPE::EQUALIZER:
        item = new Equalizer(this);
        processSubscribeItem(item);
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
        if(record_) {
            recorder_.Write(frame);
        }

        refreshCurrentData();

        calculateReturnPosition();

        return frame;
    }

    // updating playheadPos
    if(mu_ >= 1.0)
    {
        mu_ -= 1.0;
        currentIndex_++;

        if((currentIndex_ + 1) > ((int)dataset_->rows()))
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

    if(dataProcessorController_->interpolate())
    {
        dataStale_ = true;
    }

    refreshCurrentData();

    if(stepping)
    {
        step();
        dataProcessorController_->step();
    }

    for (uint i = 0; i < children_.size(); ++i)
    {
        SynthItem* item = children_[i];
        frame += item->process();
    }

    // advancing index
    calculateReturnPosition();
    mu_ += speed_ / frameRate_;

    // move masterVolume_ to target if they aren't equal.
    // Setting over the course of a single sample causes
    // audible discontinuities (clicks).
    if(!qFuzzyCompare(masterVolume_, masterVolumeTarget_))
    {
        if(masterVolume_ < masterVolumeTarget_)
        {
            masterVolume_ += 0.001f;
        } else {
            masterVolume_ -= 0.001f;
        }
    }

    frame = frame * masterVolume_ * !mute_ * 0.1f; // Multiply by 0.1 to prevent full-scale output.

    if(record_) {
        recorder_.Write(frame);
    }

    return frame;
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
    for (uint i = 0; i < subscribers_.size(); ++i)
    {
        SynthItem* item = subscribers_[i];
        item->controlProcess();
    }
    // Trigger DataProcessorController to process commands
    dataProcessorController_->controlProcess();
}

void Transport::processTransportCommand(TransportCommand cmd)
{

    switch (cmd.type) {
    case ENUMS::TRANSPORT_CMD::PAUSE:
        pause_ = (cmd.valueA == 0.0f) ? false : true;
        break;
    case ENUMS::TRANSPORT_CMD::RECORD:
        record_ = (cmd.valueA == 0.0f) ? false : true;
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
        importingDataset_ = (cmd.valueA == 0.0f) ? false : true;
        processImportDataset();
        break;
    case ENUMS::TRANSPORT_CMD::VOLUME:
        masterVolumeTarget_ = cmd.valueA;
        break;
    case ENUMS::TRANSPORT_CMD::MUTE:
        mute_ = (cmd.valueA == 0.0f) ? false : true;
        break;
    }
}

void Transport::processSubscribeItem(SynthItem *item)
{
    utility::insertUnique(item, subscribers_);
    item->setData(dataset_, &currentData_);
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
    SynthItem::controlProcess();
    if(item != this) {
        item->deleteLater();
    }
}

void Transport::processImportDataset()
{
    if(importingDataset_)
    {
        pause_ = true;
        currentData_.clear();
        currentIndex_ = 0;
        mu_ = 0.0f;
        calculateReturnPosition();
        dataStale_ = true;
        emit datasetImportReady();
    }
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
    if(!dataStale_ || !dataset_->hasData() || importingDataset_ ) return;
    currentData_ = dataProcessorController_->getData(currentIndex_, mu_);
    dataStale_ = false;
}

void Transport::calculateReturnPosition()
{
    // FIXME not on every callback
    double pos = ((double)currentIndex_ + mu_);
    returnPos_.store(pos, std::memory_order_relaxed);
}

void Transport::updatePos()
{
    float posVal = pos();
    emit posChanged(posVal);
}

} // Namespace sow.
