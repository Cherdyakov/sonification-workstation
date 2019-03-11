#include "qttransport.h"
#include "utility.h"

namespace sow {

QtTransport::QtTransport(QObject *parent) : QtSynthItem (parent)
{
    // for refreshing the playhead position
    QTimer* posTimer = new QTimer(this);
    connect(posTimer, SIGNAL(timeout()), this, SLOT(updatePos()));
    posTimer->start(33);

    dataset_ = new Dataset;

    type_ = SowEnums::ITEM::TRANSPORT;
    paused_ = true;
    loop_ = false;
    loop_begin_ = 0.0;
    loop_end_ = 0.0;
    data_stale_ = false;
    frame_rate_ = 44100;
    current_index_ = 0;
    mu_ = 0.0;
    speed_ = 1;
    return_pos_ = 0.0;
    master_volume_ = 1.0;
    interpolate_ = false;

    acceptedChildren_ = {
//        SowEnums::PARAMETER::INPUT
    };
}

/*
 Functions called from user thread
 */

void QtTransport::deleteItem(QtSynthItem *item)
{
    SynthItemCommand command;
    command.type = SowEnums::COMMAND::DELETE_ITEM;
    command.item = item;
    commandBuffer_.push(command);
}

void QtTransport::setData(QVector<double> *data, QVector<double> *mins, QVector<double> *maxes)
{
    (void)data;
    (void)mins;
    (void)maxes;
}

void QtTransport::addParent(QtSynthItem *parent)
{
    (void)parent;
}

void QtTransport::removeParent(QtSynthItem *parent)
{
    (void)parent;
}

bool QtTransport::addChild(QtSynthItem *child)
{
    if(!verify_child(child->type(), acceptedChildren_))
    {
        return false;
    }
    SynthItemCommand command;
    command.type = SowEnums::COMMAND::ADD_CHILD;
    command.item = child;
    commandBuffer_.push(command);
    return true;
}

void QtTransport::removeChild(QtSynthItem *child)
{
    SynthItemCommand command;
    command.type = SowEnums::COMMAND::REMOVE_CHILD;
    command.item = child;
    commandBuffer_.push(command);
}

void QtTransport::set_dataset(Dataset *dataset)
{
    SynthItemCommand command;
    command.type = SowEnums::COMMAND::DATA;
    command.dataset = dataset;
    commandBuffer_.push(command);
}

void QtTransport::pause(bool pause)
{
    SynthItemCommand command;
    command.type = SowEnums::COMMAND::PAUSE;
    command.bool_val = pause;
    commandBuffer_.push(command);
}

void QtTransport::set_playback_position(double pos)
{
    SynthItemCommand command;
    command.type = SowEnums::COMMAND::POSITION;
    command.doubles.push_back(pos);
    commandBuffer_.push(command);
}

void QtTransport::set_speed(int speed)
{
    SynthItemCommand command;
    command.type = SowEnums::COMMAND::SPEED;
    command.ints.push_back(speed);
    commandBuffer_.push(command);
}

void QtTransport::set_looping(bool looping)
{
    SynthItemCommand command;
    command.type = SowEnums::COMMAND::LOOP;
    command.bool_val = looping;
    commandBuffer_.push(command);
}

void QtTransport::set_loop_points(double begin, double end)
{
    SynthItemCommand command;
    command.type = SowEnums::COMMAND::LOOP_POINTS;
    command.doubles.push_back(begin);
    command.doubles.push_back(end);
    commandBuffer_.push(command);
}

void QtTransport::set_interpolate(bool interpolate)
{
    SynthItemCommand command;
    command.type = SowEnums::COMMAND::INTERPOLATE;
    command.bool_val = interpolate;
    commandBuffer_.push(command);
}

void QtTransport::subscribeItem(QtSynthItem *item)
{
    SynthItemCommand command;
    command.type = SowEnums::COMMAND::SUBSCRIBE;
    command.item = item;
    commandBuffer_.push(command);
}

void QtTransport::unsubscribe_item(QtSynthItem *item)
{
    SynthItemCommand command;
    command.type = SowEnums::COMMAND::UNSUBSCRIBE;
    command.item = item;
    commandBuffer_.push(command);
}

QtSynthItem* QtTransport::createItem(SowEnums::ITEM type)
{
    QtSynthItem* item;

    switch (type){
    case SowEnums::ITEM::OUT:
        item = this;
        break;
    case SowEnums::ITEM::OSCILLATOR:
        item = new QtOscillator();
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
        item = NULL;
        break;
    }
//    item->setData(&current_data_column_, &dataset_->mins_, &dataset_->maxes_);
    return item;
}

double QtTransport::get_playback_position()
{
    return return_pos_;
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
        current_index_++;

        if((current_index_ + 1) > (dataset_->width_))
        {
            current_index_ = 0;
        }
        data_stale_ = true;
        stepping = true;
    }

    if(loop_ && (loop_begin_ != loop_end_))
    {
        if(((double)current_index_ + mu_) > loop_end_)
        {
            current_index_ = (int)loop_begin_;
            mu_ = (loop_begin_ - current_index_);
            data_stale_ = true;
        }
        else if(((double)current_index_ + mu_) < loop_begin_)
        {
            current_index_ = (int)loop_begin_;
            mu_ = (loop_begin_ - current_index_);
            data_stale_ = true;
        }
    }

    if(interpolate_)
    {
        data_stale_ = true;
    }

    if(data_stale_)
    {
        retrieveNextDataColumn();
        data_stale_ = false;
    }

    if(stepping)
    {
        step();
    }

    for (unsigned int i = 0; i < children_.size(); ++i)
    {
        QtSynthItem* item = children_[i];
        frame += item->process();
    }

    // advancing index
    calculateReturnPosition();
    mu_ += ((double)speed_ / frame_rate_);

    return frame;// * master_volume_;
}

void QtTransport::step()
{
    for (unsigned int i = 0; i < children_.size(); ++i)
    {
        QtSynthItem* item = children_[i];
        item->step();
    }
}

void QtTransport::controlProcess()
{
    // Process buffered transport commands first
    while(commandBuffer_.pop(&currentCommand_))
    {
        processCommand(currentCommand_);
    }
    // Have all SynthItems process their buffered commands
    for (unsigned int i = 0; i < subscribers_.size(); ++i)
    {
        QtSynthItem* item = subscribers_[i];
        item->controlProcess();
    }
}

void QtTransport::on_datasetChanged(Dataset *dataset)
{
    pause(true);
    set_dataset(dataset);
}

void QtTransport::on_pausedChanged(bool p)
{
    pause(p);
}

void QtTransport::on_posChanged(double pos)
{
    set_playback_position(pos);
}

void QtTransport::on_speedChanged(int speed)
{
    set_speed(speed);
}

void QtTransport::on_loopingChanged(bool looping)
{
    set_looping(looping);
}

void QtTransport::on_loopPointsChanged(double begin, double end)
{
    set_loop_points(begin, end);
}

void QtTransport::on_interpolateChanged(bool interpolate)
{
    set_interpolate(interpolate);
}

double QtTransport::getPos()
{
    double pos;
    pos = get_playback_position();
    return pos;
}

void QtTransport::processCommand(SynthItemCommand command)
{
//    COMMAND type = command.type;

//    switch (type) {
//    case SowEnums::COMMAND::DATA:
//        process_set_dataset(command.dataset);
//        break;
//    case SowEnums::COMMAND::ADD_CHILD:
//        processAddChild(command.item, command.parameter);
//        break;
//    case SowEnums::COMMAND::REMOVE_CHILD:
//        processRemoveChild(command.item);
//        break;
//    case SowEnums::COMMAND::MUTE:
//        muted_ = command.bool_val;
//        break;
//    case SowEnums::COMMAND::PAUSE:
//        paused_ = command.bool_val;
//        break;
//    case SowEnums::COMMAND::POSITION:
//        process_set_playback_position(command.doubles[0]);
//        break;
//    case SowEnums::COMMAND::SPEED:
//        speed_ = command.ints[0];
//        break;
//    case SowEnums::COMMAND::LOOP:
//        loop_ = command.bool_val;
//        break;
//    case SowEnums::COMMAND::LOOP_POINTS:
//        loop_begin_ = command.doubles[0];
//        loop_end_ = command.doubles[1];
//        break;
//    case SowEnums::COMMAND::INTERPOLATE:
//        interpolate_ = command.bool_val;
//        break;
//    case SowEnums::COMMAND::DELETE:
//        processDelete();
//        break;
//    case SowEnums::COMMAND::DELETE_ITEM:
//        process_delete_item(command.item);
//        break;
//    case SowEnums::COMMAND::SUBSCRIBE:
//        process_subscribe_item(command.item);
//        break;
//    case SowEnums::COMMAND::UNSUBSCRIBE:
//        process_unsubscribe_item(command.item);
//        break;
//    default:
//        break;
//    }
}

void QtTransport::processSubscribeItem(QtSynthItem *item)
{
    subscribers_.push_back(item);
}

void QtTransport::processUnsubscribeItem(QtSynthItem *item)
{
    remove_item(item, &subscribers_);
}

void QtTransport::processSetDataset(Dataset *dataset)
{
    paused_ = true;
    dataset_ = dataset;
    current_data_column_.clear();
    current_index_ = 0;
    mu_ = 0.0;
    calculateReturnPosition();
    current_data_column_.resize(dataset_->height_);
}

void QtTransport::processSetPlaybackPosition(double pos)
{
    unsigned int newIdx = (int)pos;
    if(current_index_ != newIdx)
    {
        data_stale_ = true;
        current_index_ = newIdx;
    }
    mu_ = (pos - current_index_);
}

void QtTransport::retrieveNextDataColumn()
{
    if(interpolate_)
    {
        unsigned int next_index = current_index_ + 1;
        if(next_index >= dataset_->width_)
        {
            next_index = 0;
        }
        current_data_column_ = interpolate(dataset_->get_column(current_index_), dataset_->get_column(next_index), mu_);
    }
    else {
        current_data_column_ = dataset_->get_column(current_index_);
    }
}

void QtTransport::calculateReturnPosition()
{
    // FIXME not on every callback
    double pos = ((double)current_index_ + mu_);
    return_pos_.store(pos, std::memory_order_relaxed);
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
    double pos = get_playback_position();
    emit posChanged(pos);
}

} // Namespace sow.
