#include "qttransport.h"
#include "utility.h"

using namespace sow;

QtTransport::QtTransport(QObject *parent)
{
    // for refreshing the playhead position
    QTimer* posTimer = new QTimer(this);
    connect(posTimer, SIGNAL(timeout()), this, SLOT(updatePos()));
    posTimer->start(33);

    dataset_ = new Dataset;

    my_type_ = ITEM::TRANSPORT;
    my_child_type_ = PARAMETER::OUTPUT;
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

    accepted_children_ = {
        PARAMETER::INPUT
    };
}

/*
 Functions called from user thread
 */

void QtTransport::deleteSelf()
{
    SynthItemCommand command;
    command.type = COMMAND::DELETE;
    command_buffer_.push(command);
}

void QtTransport::deleteItem(QtSynthItem *item)
{
    SynthItemCommand command;
    command.type = COMMAND::DELETE_ITEM;
    command.item = item;
    command_buffer_.push(command);
}

ITEM QtTransport::getType()
{
    return my_type_;
}

void QtTransport::setData(std::vector<double> *data, std::vector<double> *mins, std::vector<double> *maxes)
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

bool QtTransport::addChild(QtSynthItem *child, PARAMETER param)
{
    if(!verify_child(param, accepted_children_))
    {
        return false;
    }
    SynthItemCommand command;
    command.type = COMMAND::ADD_CHILD;
    command.parameter = param;
    command.item = child;
    command_buffer_.push(command);
    return true;
}

void QtTransport::removeChild(QtSynthItem *child)
{
    SynthItemCommand command;
    command.type = COMMAND::REMOVE_CHILD;
    command.item = child;
    command_buffer_.push(command);
}

void QtTransport::mute(bool mute)
{
    SynthItemCommand command;
    command.type = COMMAND::MUTE;
    command.bool_val = mute;
    command_buffer_.push(command);
}

void QtTransport::set_dataset(Dataset *dataset)
{
    SynthItemCommand command;
    command.type = COMMAND::DATA;
    command.dataset = dataset;
    command_buffer_.push(command);
}

void QtTransport::pause(bool pause)
{
    SynthItemCommand command;
    command.type = COMMAND::PAUSE;
    command.bool_val = pause;
    command_buffer_.push(command);
}

void QtTransport::set_playback_position(double pos)
{
    SynthItemCommand command;
    command.type = COMMAND::POSITION;
    command.doubles.push_back(pos);
    command_buffer_.push(command);
}

void QtTransport::set_speed(int speed)
{
    SynthItemCommand command;
    command.type = COMMAND::SPEED;
    command.ints.push_back(speed);
    command_buffer_.push(command);
}

void QtTransport::set_looping(bool looping)
{
    SynthItemCommand command;
    command.type = COMMAND::LOOP;
    command.bool_val = looping;
    command_buffer_.push(command);
}

void QtTransport::set_loop_points(double begin, double end)
{
    SynthItemCommand command;
    command.type = COMMAND::LOOP_POINTS;
    command.doubles.push_back(begin);
    command.doubles.push_back(end);
    command_buffer_.push(command);
}

void QtTransport::set_interpolate(bool interpolate)
{
    SynthItemCommand command;
    command.type = COMMAND::INTERPOLATE;
    command.bool_val = interpolate;
    command_buffer_.push(command);
}

void QtTransport::subscribeItem(QtSynthItem *item)
{
    SynthItemCommand command;
    command.type = COMMAND::SUBSCRIBE;
    command.item = item;
    command_buffer_.push(command);
}

void QtTransport::unsubscribe_item(QtSynthItem *item)
{
    SynthItemCommand command;
    command.type = COMMAND::UNSUBSCRIBE;
    command.item = item;
    command_buffer_.push(command);
}

QtSynthItem* QtTransport::createItem(QT_ITEM type)
{
    QtSynthItem* item;

    switch (type){
//    case QtSynthItem::ITEM::OSCILLATOR:
//        item = new Oscillator();
//        break;
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
    item->setData(&current_data_column_, &dataset_->mins_, &dataset_->maxes_);
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
        calculate_return_position();
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
        retrieve_next_data_column();
        data_stale_ = false;
    }

    if(stepping)
    {
        step();
    }

    for (unsigned int i = 0; i < inputs_.size(); ++i)
    {
        QtSynthItem* item = inputs_[i];
        frame += item->process();
    }

    // advancing index
    calculate_return_position();
    mu_ += ((double)speed_ / frame_rate_);

    return frame;// * master_volume_;
}

void QtTransport::step()
{
    for (unsigned int i = 0; i < inputs_.size(); ++i)
    {
        QtSynthItem* item = inputs_[i];
        item->step();
    }
}

void QtTransport::controlProcess()
{
    for (unsigned int i = 0; i < subscribers_.size(); ++i)
    {
        QtSynthItem* item = subscribers_[i];
        item->controlProcess();
    }
    if(!command_buffer_.empty())
    {
        retrieveCommands();
    }
}

bool QtTransport::getMute()
{
    return muted_;
}

std::vector<QtSynthItem *> QtTransport::getParents()
{
    std::vector<QtSynthItem*> vec;
    return vec;
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

void QtTransport::retrieveCommands()
{
    while(command_buffer_.pop(&current_command_))
    {
        processCommand(current_command_);
    }
}

void QtTransport::processCommand(SynthItemCommand command)
{
    COMMAND type = command.type;

    switch (type) {
    case COMMAND::DATA:
        process_set_dataset(command.dataset);
        break;
    case COMMAND::ADD_CHILD:
        processAddChild(command.item, command.parameter);
        break;
    case COMMAND::REMOVE_CHILD:
        processRemoveChild(command.item);
        break;
    case COMMAND::MUTE:
        muted_ = command.bool_val;
        break;
    case COMMAND::PAUSE:
        paused_ = command.bool_val;
        break;
    case COMMAND::POSITION:
        process_set_playback_position(command.doubles[0]);
        break;
    case COMMAND::SPEED:
        speed_ = command.ints[0];
        break;
    case COMMAND::LOOP:
        loop_ = command.bool_val;
        break;
    case COMMAND::LOOP_POINTS:
        loop_begin_ = command.doubles[0];
        loop_end_ = command.doubles[1];
        break;
    case COMMAND::INTERPOLATE:
        interpolate_ = command.bool_val;
        break;
    case COMMAND::DELETE:
        processDelete();
        break;
    case COMMAND::DELETE_ITEM:
        process_delete_item(command.item);
        break;
    case COMMAND::SUBSCRIBE:
        process_subscribe_item(command.item);
        break;
    case COMMAND::UNSUBSCRIBE:
        process_unsubscribe_item(command.item);
        break;
    default:
        break;
    }
}

void QtTransport::processAddChild(QtSynthItem *child, PARAMETER parameter)
{
    switch (parameter){
    case PARAMETER::INPUT:
        insert_item_unique(child, &inputs_);
        break;
    case PARAMETER::AMPLITUDE:
        insert_item_unique(child, &inputs_);
        break;
    default:
        break; //incompatible child type
    }
    child->addParent(this);
}

void QtTransport::processRemoveChild(QtSynthItem *child)
{
    remove_item(child, &inputs_);
    remove_item(child, &amods_);
}

void QtTransport::processDelete()
{
    for(unsigned int i = 0; i < inputs_.size(); i++) {
        QtSynthItem* child = inputs_[i];
        child->removeParent(this);
    }
    for(unsigned int i = 0; i < amods_.size(); i++) {
        QtSynthItem* child = amods_[i];
        child->removeParent(this);
    }
    delete this;
}

void QtTransport::process_delete_item(QtSynthItem *item)
{
    process_unsubscribe_item(item);
    item->deleteSelf();
    item->controlProcess();
}

void QtTransport::process_subscribe_item(QtSynthItem *item)
{
    subscribers_.push_back(item);
}

void QtTransport::process_unsubscribe_item(QtSynthItem *item)
{
    remove_item(item, &subscribers_);
}

void QtTransport::process_set_dataset(Dataset *dataset)
{
    paused_ = true;
    dataset_ = dataset;
    current_data_column_.clear();
    current_index_ = 0;
    mu_ = 0.0;
    calculate_return_position();
    current_data_column_.resize(dataset_->height_);
}

void QtTransport::process_set_playback_position(double pos)
{
    unsigned int newIdx = (int)pos;
    if(current_index_ != newIdx)
    {
        data_stale_ = true;
        current_index_ = newIdx;
    }
    mu_ = (pos - current_index_);
}

void QtTransport::retrieve_next_data_column()
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

void QtTransport::calculate_return_position()
{
    // FIXME not on every callback
    double pos = ((double)current_index_ + mu_);
    return_pos_.store(pos, std::memory_order_relaxed);
}

std::vector<double> QtTransport::interpolate(std::vector<double> first, std::vector<double> second, double mu)
{
    std::vector<double> vec;
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
