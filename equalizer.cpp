#include "equalizer.h"
#include "utility.h"

namespace son {

Equalizer::Equalizer()
{
    my_type_ = ITEM::EQUALIZER;
    muted_ = false;
    frequency_ = 1000;
    frequency_fixed_ = true;
    frequency_scaled_ = true;
    frequency_low_ = 100;
    frequency_high_ = 16000;
    frequency_exponent_ = 1;

    resonance_ = 1;
    resonance_fixed_ = true;
    resonance_scaled_ = true;
    resonance_low_ = 0;
    resonance_high_ = 10;
    resonance_exponent_ = 1;

    accepted_children_ = {
        PARAMETER::INPUT,
        PARAMETER::AMPLITUDE
    };
}

void Equalizer::delete_item()
{
    SynthItemCommand command;
    command.type = COMMAND::DELETE;
    command_buffer_.push(command);
}

SynthItem::ITEM Equalizer::get_type()
{
    return my_type_;
}

void Equalizer::set_data(std::vector<double> *data, std::vector<double> *mins, std::vector<double> *maxes)
{
    SynthItemCommand command;
    command.type = COMMAND::DATA;
    command.data = data;
    command.mins = mins;
    command.maxes = maxes;
    command_buffer_.push(command);
}

void Equalizer::add_parent(SynthItem *parent)
{
    SynthItemCommand command;
    command.type = COMMAND::ADD_PARENT;
    command.item = parent;
    command_buffer_.push(command);
}

void Equalizer::remove_parent(SynthItem *parent)
{
    SynthItemCommand command;
    command.type = COMMAND::REMOVE_PARENT;
    command.item = parent;
    command_buffer_.push(command);
}

bool Equalizer::add_child(SynthItem *child, SynthItem::PARAMETER param)
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

void Equalizer::remove_child(SynthItem *child)
{
    SynthItemCommand command;
    command.type = COMMAND::REMOVE_CHILD;
    command.item = child;
    command_buffer_.push(command);
}

void Equalizer::mute(bool mute)
{
    SynthItemCommand command;
    command.type = COMMAND::MUTE;
    command.bool_val = mute;
    command_buffer_.push(command);
}

void Equalizer::set_frequency(double frequency)
{
    SynthItemCommand command;
    command.type = COMMAND::PARAM;
    command.parameter = PARAMETER::FREQUENCY;
    command.doubles.push_back(frequency);
    command_buffer_.push(command);
}

void Equalizer::set_frequency_fixed(bool fixed)
{
    SynthItemCommand command;
    command.type = COMMAND::FIXED;
    command.parameter = PARAMETER::FREQUENCY;
    command.bool_val = fixed;
    command_buffer_.push(command);
}

void Equalizer::set_frequency_indexes(std::vector<int> indexes)
{
    SynthItemCommand command;
    command.type = COMMAND::INDEXES;
    command.parameter = PARAMETER::FREQUENCY;
    command.ints.assign(indexes.begin(), indexes.end());
    command_buffer_.push(command);
}

void Equalizer::set_frequency_scaled(bool scaled)
{
    SynthItemCommand command;
    command.type = COMMAND::SCALED;
    command.parameter = PARAMETER::FREQUENCY;
    command.bool_val = scaled;
    command_buffer_.push(command);
}

void Equalizer::set_frequency_scale_vals(double low, double high, double exp)
{
    SynthItemCommand command;
    command.type = COMMAND::SCALE_VALS;
    command.parameter = PARAMETER::FREQUENCY;
    command.doubles.push_back(low);
    command.doubles.push_back(high);
    command.doubles.push_back(exp);
    command_buffer_.push(command);
}

void Equalizer::set_resonance(double resonance)
{
    SynthItemCommand command;
    command.type = COMMAND::PARAM;
    command.parameter = PARAMETER::RESONANCE;
    command.doubles.push_back(resonance);
    command_buffer_.push(command);
}

void Equalizer::set_resonance_fixed(bool fixed)
{
    SynthItemCommand command;
    command.type = COMMAND::FIXED;
    command.parameter = PARAMETER::RESONANCE;
    command.bool_val = fixed;
    command_buffer_.push(command);
}

void Equalizer::set_resonance_indexes(std::vector<int> indexes)
{
    SynthItemCommand command;
    command.type = COMMAND::INDEXES;
    command.parameter = PARAMETER::RESONANCE;
    command.ints.assign(indexes.begin(), indexes.end());
    command_buffer_.push(command);
}

void Equalizer::set_resonance_scaled(bool scaled)
{
    SynthItemCommand command;
    command.type = COMMAND::SCALED;
    command.parameter = PARAMETER::RESONANCE;
    command.bool_val = scaled;
    command_buffer_.push(command);
}

void Equalizer::set_resonance_scale_vals(double low, double high, double exp)
{
    SynthItemCommand command;
    command.type = COMMAND::SCALE_VALS;
    command.parameter = PARAMETER::RESONANCE;
    command.doubles.push_back(low);
    command.doubles.push_back(high);
    command.doubles.push_back(exp);
    command_buffer_.push(command);
}

void Equalizer::set_filter_type(SynthItem::FILTER_TYPE type)
{
    SynthItemCommand command;
    command.type = COMMAND::FILTER_TYPE;
    command.ints.push_back((int) type);
    command_buffer_.push(command);
}

// Generate a frame of output
Frame Equalizer::process()
{
    Frame frame;

    if(!command_buffer_.empty())
    {
        retrieve_commands();
    }

    if(muted_ || inputs_.size() < 1)
    {
        return frame;
    }

    // generate frame from all inputs
    for (unsigned int i = 0; i < inputs_.size(); ++i) {
        frame += inputs_[i]->process();
    }
    frame /= inputs_.size();

    // set the filter parameters
    set_filter();

    // filter input
    float filtered_left = filter_left_(frame.left);
    float filtered_right = filter_right_(frame.right);
    frame.left = filtered_left;
    frame.right = filtered_right;

    // visit amplitude modulating children
    if(!amods_.empty())
    {
        Frame am_frame = visit_children(amods_);
        frame *= am_frame;
    }

    return frame;
}

void Equalizer::step()
{
    for (unsigned int i = 0; i < amods_.size(); i++) {
        SynthItem *item = amods_[i];
        item->step();
    }
}

void Equalizer::retrieve_commands()
{
    while(command_buffer_.pop(&current_command_))
    {
        process_command(current_command_);
    }
}

void Equalizer::process_command(SynthItem::SynthItemCommand command)
{
    COMMAND type = command.type;

    switch (type) {
    case COMMAND::DATA:
        process_set_data(command.data, command.mins, command.maxes);
        break;
    case COMMAND::ADD_CHILD:
        process_add_child(command.item, command.parameter);
        break;
    case COMMAND::REMOVE_CHILD:
        process_remove_child(command.item);
        break;
    case COMMAND::ADD_PARENT:
        insert_item_unique(command.item, &parents_);
        break;
    case COMMAND::REMOVE_PARENT:
        erase_item(command.item, &parents_);
        break;
    case COMMAND::MUTE:
        muted_ = command.bool_val;
        break;
    case COMMAND::PARAM:
        process_set_param_value(command.doubles[0], command.parameter);
        break;
    case COMMAND::FIXED:
        process_set_param_fixed(command.bool_val, command.parameter);
        break;
    case COMMAND::INDEXES:
        process_set_param_indexes(command.ints, command.parameter);
        break;
    case COMMAND::SCALED:
        process_set_param_scaled(command.bool_val, command.parameter);
        break;
    case COMMAND::SCALE_VALS:
        process_set_param_scale_vals(command.doubles[0], command.doubles[1], command.doubles[2], command.parameter);
        break;
    case COMMAND::DELETE:
        process_delete_item();
        break;
    case COMMAND::FILTER_TYPE:
        process_set_filter_type((FILTER_TYPE)command.ints[0]);
    default:
        break;
    }
}

void Equalizer::process_add_child(SynthItem *child, SynthItem::PARAMETER parameter)
{
    switch (parameter){
    case PARAMETER::INPUT:
        insert_item_unique(child, &inputs_);
        child->add_parent(this);
        break;
    case PARAMETER::AMPLITUDE:
        insert_item_unique(child, &amods_);
        child->add_parent(this);
        break;
    default:
        break; //incompatible child type
    }
}

void Equalizer::process_remove_child(SynthItem *child)
{
    erase_item(child, &inputs_);
    erase_item(child, &amods_);
}

void Equalizer::process_delete_item()
{
    remove_as_child(this, parents_);
    remove_as_parent(this, inputs_);
    remove_as_parent(this, amods_);
    delete this;
}

void Equalizer::process_set_data(std::vector<double> *data, std::vector<double> *mins, std::vector<double> *maxes)
{
    data_ = data;
    mins_ = mins;
    maxes_ = maxes;
}

void Equalizer::process_set_param_value(double val, SynthItem::PARAMETER param)
{
    if(param == PARAMETER::FREQUENCY)
    {
        frequency_ = val;
    }
    else if(param == PARAMETER::RESONANCE)
    {
        resonance_ = val;
    }
}

void Equalizer::process_set_param_fixed(bool fixed, SynthItem::PARAMETER param)
{
    if(param == PARAMETER::FREQUENCY)
    {
        frequency_fixed_ = fixed;
    }
    else if(param == PARAMETER::RESONANCE)
    {
        resonance_fixed_ = fixed;
    }
}

void Equalizer::process_set_param_indexes(std::vector<int> indexes, SynthItem::PARAMETER param)
{
    if(param == PARAMETER::FREQUENCY)
    {
        frequency_indexes_ = indexes;
    }
    else if(param == PARAMETER::RESONANCE)
    {
        resonance_indexes_ = indexes;
    }
}

void Equalizer::process_set_param_scaled(bool scaled, SynthItem::PARAMETER param)
{
    if(param == PARAMETER::FREQUENCY)
    {
        frequency_scaled_ = scaled;
    }
    else if(param == PARAMETER::RESONANCE)
    {
        resonance_scaled_ = scaled;
    }
}

void Equalizer::process_set_param_scale_vals(double low, double high, double exp, SynthItem::PARAMETER param)
{
    if(param == PARAMETER::FREQUENCY)
    {
        frequency_low_ = low;
        frequency_high_ = high;
        frequency_exponent_ = exp;
    }
    else if(param ==  PARAMETER::RESONANCE)
    {
        resonance_low_ = low;
        resonance_high_ = high;
        resonance_exponent_ = exp;
    }
}

void Equalizer::process_set_filter_type(SynthItem::FILTER_TYPE type)
{
    if(filter_type_ != type)
    {
        filter_type_ = type;
        gam::FilterType gam_type = convert_filter_type(filter_type_);
        filter_left_.type(gam_type);
        filter_right_.type(gam_type);
    }
}

void Equalizer::set_filter()
{
    double frequency = calculate_filter_frequency();
    double resonance = calculate_filter_resonance();
    filter_left_.set(frequency, resonance);
    filter_right_.set(frequency, resonance);
}

gam::FilterType Equalizer::convert_filter_type(FILTER_TYPE type)
{
    gam::FilterType gam_type;
    switch (type) {
    case FILTER_TYPE::LOW_PASS:
        gam_type = gam::FilterType::LOW_PASS;
        break;
    case FILTER_TYPE::HIGH_PASS:
        gam_type =  gam::FilterType::HIGH_PASS;
        break;
    case FILTER_TYPE::PEAK:
        gam_type =  gam::FilterType::BAND_PASS;
        break;
    case FILTER_TYPE::NOTCH:
        gam_type =  gam::FilterType::BAND_REJECT;
        break;
    default:
        gam_type = gam::FilterType::LOW_PASS;
        break;
    }
    return gam_type;
}

double Equalizer::calculate_filter_frequency()
{
    double frequency;
    if (frequency_fixed_ == true || frequency_indexes_.size() < 1) //no data mappings, use fixed freq
    {
        frequency = frequency_;
    }
    else //map each indexed value from the data row to the freq of a generator
    {
        int idx = frequency_indexes_[0];
        frequency = data_->at(idx);
        if(frequency_scaled_)
        {
            frequency = scale(frequency, mins_->at(idx), maxes_->at(idx),
                              frequency_low_, frequency_high_, frequency_exponent_);
        }
    }
    return frequency;
}

double Equalizer::calculate_filter_resonance()
{
    double resonance;
    if (resonance_fixed_ == true || resonance_indexes_.size() < 1) //no data mappings, use fixed resonance
    {
        resonance = resonance_;
    }
    else //map each indexed value from the data row to the resonance of a generator
    {
        int idx = resonance_indexes_[0];
        resonance = data_->at(idx);
        if(resonance_scaled_)
        {
            resonance = scale(resonance, mins_->at(idx), maxes_->at(idx),
                              resonance_low_, resonance_high_, resonance_exponent_);
        }
    }
    return resonance;
}

} // namespace son
