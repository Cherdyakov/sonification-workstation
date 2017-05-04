#include "transport.h"

namespace son {

Transport::Transport()
{
    paused_ = true;
    loop_ = false;
    loop_begin_ = 0.0;
    loop_end_ = 0.0;
    data_stale = false;
    block_size_ = 512;
    sample_rate_ = 44100;
    data_width_ = 0;
    data_height_ = 0;
    current_index_ = 0;
    mu_ = 0.0;
    speed_ = 1.0;
    return_pos = 0.0;
    master_volume_ = 1.0;
    interpolate_ = false;

    accepted_children_ = {
        SynthItem::PARAMETER::INPUT
    };
}

Transport::~Transport()
{

}

/*
 Functions called from user thread
 */

void Transport::delete_item()
{
    SynthItemCommand command;
    command.type = COMMAND::DELETE;
    command_buffer_.push(command);
}

SynthItem::ITEM Transport::get_type()
{
    return my_type_;
}

void Transport::set_data(std::vector<double> *data, std::vector<double> *mins, std::vector<double> *maxes)
{
    (void)data;
    (void)mins;
    (void)maxes;
}

void Transport::add_parent(SynthItem *parent)
{
    SynthItemCommand command;
    command.type = COMMAND::ADD_PARENT;
    command.item = parent;
    command_buffer_.push(command);
}

void Transport::remove_parent(SynthItem *parent)
{
    SynthItemCommand command;
    command.type = COMMAND::REMOVE_PARENT;
    command.item = parent;
    command_buffer_.push(command);
}

bool Transport::add_child(SynthItem *child, SynthItem::PARAMETER param)
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

void Transport::remove_child(SynthItem *child)
{
    SynthItemCommand command;
    command.type = COMMAND::REMOVE_CHILD;
    command.item = child;
    command_buffer_.push(command);
}

void Transport::mute(bool mute)
{
    SynthItemCommand command;
    command.type = COMMAND::MUTE;
    command.bool_val = mute;
    command_buffer_.push(command);
}

void Transport::set_dataset(std::vector<double> *dataset, unsigned int height, unsigned int width)
{
    SynthItemCommand command;
    command.type = COMMAND::DATA;
    command.data = dataset;
    command.ints.push_back(height);
    command.ints.push_back(width);
    command_buffer_.push(command);
}

void Transport::pause(bool pause)
{
    SynthItemCommand command;
    command.type = COMMAND::PAUSE;
    command.bool_val = pause;
    command_buffer_.push(command);
}

void Transport::set_playback_position(double pos)
{
    SynthItemCommand command;
    command.type = COMMAND::POSITION;
    command.doubles.push_back(pos);
    command_buffer_.push(command);
}

void Transport::set_speed(double speed)
{
    SynthItemCommand command;
    command.type = COMMAND::SPEED;
    command.doubles.push_back(speed);
    command_buffer_.push(command);
}

void Transport::set_looping(bool looping)
{
    SynthItemCommand command;
    command.type = COMMAND::LOOP;
    command.bool_val = looping;
    command_buffer_.push(command);
}

void Transport::set_loop_points(double begin, double end)
{
    SynthItemCommand command;
    command.type = COMMAND::LOOP_POINTS;
    command.doubles.push_back(begin);
    command.doubles.push_back(end);
    command_buffer_.push(command);
}

void Transport::set_interpolate(bool interpolate)
{
    SynthItemCommand command;
    command.type = COMMAND::INTERPOLATE;
    command.bool_val = interpolate;
    command_buffer_.push(command);
}

SynthItem* Transport::create_item(SynthItem::ITEM type)
{
    SynthItem* item;

    switch (type){
    case SynthItem::ITEM::TRANSPORT:
        item = NULL;
        break;
    case SynthItem::ITEM::OSCILLATOR:
        item = new Oscillator();
        item->set_data(&current_data_column_, &min_data_vals_, &max_data_vals_);
        break;
    case SynthItem::ITEM::AUDIFIER:
        item = new Audifier();
        item->set_data(&current_data_column_, &min_data_vals_, &max_data_vals_);
        break;
    case SynthItem::ITEM::MODULATOR:
        item = new Modulator();
        item->set_data(&current_data_column_, &min_data_vals_, &max_data_vals_);
        break;
    default:
        item = NULL;
        break;
    }
    return item;
}

double Transport::get_playback_position()
{
    return return_pos;
}

/*
 Functions called from audio callback thread
 */

float Transport::process()
{
    float s = 0.0;

    if(!command_buffer_.empty())
    {
        retrieve_commands();
    }

    if(paused_)
    {
        calculate_return_position();
        return s;
    }

    // updating playheadPos
    if(mu_ >= 1.0)
    {
        mu_ -= 1.0;
        current_index_++;

        if((current_index_ + 1) > (data_width_))
        {
            current_index_ = 0;
        }
        data_stale = true;
    }

    if(loop_ && (loop_begin_ != loop_end_))
    {
        if(((double)current_index_ + mu_) > loop_end_)
        {
            current_index_ = (int)loop_begin_;
            mu_ = (loop_begin_ - current_index_);
            data_stale = true;
        }
        else if(((double)current_index_ + mu_) < loop_begin_)
        {
            current_index_ = (int)loop_begin_;
            mu_ = (loop_begin_ - current_index_);
            data_stale = true;
        }
    }

    if(interpolate_)
    {
        data_stale = true;
    }

    if(data_stale)
    {
        retrieve_next_data_column();
        data_stale = false;
    }

    for (unsigned int i = 0; i < inputs_.size(); ++i) {
        SynthItem* item = inputs_[i];
        s += item->process();
    }

    // advancing index
    calculate_return_position();
    mu_ += (speed_ / sample_rate_);

    return s * master_volume_;
}

void Transport::retrieve_commands()
{
    while(command_buffer_.pop(&current_command_))
    {
        process_command(current_command_);
    }
}

void Transport::process_command(SynthItemCommand command)
{
    COMMAND type = command.type;

    switch (type) {
    case COMMAND::DATA:
        process_set_dataset(command.data, command.ints[0], command.ints[1]);
        break;
    case COMMAND::ADD_CHILD:
        process_add_child(command.item, command.parameter);
        break;
    case COMMAND::REMOVE_CHILD:
        process_remove_child(command.item);
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
        speed_ = command.doubles[0];
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
    default:
        break;
    }
}

void Transport::process_add_child(SynthItem *child, SynthItem::PARAMETER parameter)
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
    child->add_parent(this);
}

void Transport::process_remove_child(SynthItem *child)
{
    erase_item(child, &inputs_);
    erase_item(child, &amods_);
}

void Transport::process_delete_item()
{
    for(unsigned int i = 0; i < inputs_.size(); i++) {
        SynthItem* child = inputs_[i];
        child->remove_parent(this);
    }
    for(unsigned int i = 0; i < amods_.size(); i++) {
        SynthItem* child = amods_[i];
        child->remove_parent(this);
    }
    delete this;
}

void Transport::process_set_dataset(std::vector<double> *dataset, unsigned int height, unsigned int width)
{
    paused_ = true;
    dataset_ = dataset;
    data_width_ = width;
    current_data_column_.clear();
    current_index_ = 0;
    mu_ = 0.0;
    calculate_return_position();
    if(data_height_ != height)
    {
        data_height_ = height;
        current_data_column_.resize(data_height_);
    }
    calculate_min_max();
}

void Transport::process_set_playback_position(double pos)
{
    unsigned int newIdx = (int)pos;
    if(current_index_ != newIdx)
    {
        data_stale = true;
        current_index_ = newIdx;
    }
    mu_ = (pos - current_index_);
}

void Transport::retrieve_next_data_column()
{
    if(interpolate_)
    {
        for(unsigned int i = 0; i < data_height_; i++)
        {
            unsigned int idx = ((data_width_ * i) + current_index_);
            unsigned int nextIdx = idx + 1;
            if(nextIdx > (data_width_ * i) + (data_width_ - 1)) {
                nextIdx -= data_width_;
            }
            double val = (*dataset_)[idx];
            double valNext = (*dataset_)[nextIdx];
            current_data_column_[i] = ((1 - mu_) * val) + (mu_ * valNext);
        }
    }
    else {
        for(unsigned int i = 0; i < data_height_; i++)
        {
            unsigned int idx = ((data_width_ * i) + current_index_);
            current_data_column_[i] = (*dataset_)[idx];
        }
    }
}

void Transport::calculate_return_position()
{
    // FIXME not on every callback
    double pos = ((double)current_index_ + mu_);
    return_pos.store(pos, std::memory_order_relaxed);
}

void Transport::calculate_min_max()
{
    double min;
    double max;
    min_data_vals_.clear();
    max_data_vals_.clear();
    for(unsigned int i = 0; i < data_height_; i++)
    {
        for(unsigned int j = 0; j < data_width_; j++)
        {
            unsigned int idx = i * data_width_ + j;
            double value = dataset_->at(idx);
            if(j == 0)
            {
                min = max = value;
            }
            else if(value < min)
            {
                min = value;
            }
            else if(value > max)
            {
                max = value;
            }
        }
        min_data_vals_.push_back(min);
        max_data_vals_.push_back(max);
    }
}

} //namespace son
