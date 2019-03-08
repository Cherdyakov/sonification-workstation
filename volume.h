#ifndef VOLUME_H
#define VOLUME_H

#include "synthitem.h"

namespace sow {

class Volume : public SynthItem
{
public:
    Volume();

    // helper when deleting item contained in synth tree
    void delete_self() override;
    // interface overrides
    ITEM get_type() override;
    void set_data(std::vector<double>* data,
                  std::vector<double>* mins,
                  std::vector<double>* maxes) override;
    void add_parent(SynthItem* parent) override;
    void remove_parent(SynthItem* parent) override;
    bool add_child(SynthItem *child, PARAMETER param) override;
    void remove_child(SynthItem *child) override;
    void mute(bool mute) override;
    // volume parameter accessors
    void set_volume(double volume);
    void set_volume_fixed(bool fixed);
    void set_volume_indexes(std::vector<int> indexes);
    void set_volume_scaled(bool scaled);
    void set_volume_scale_low(double low);
    void set_volume_scale_high(double high);
    void set_volume_scale_exponent(double exponent);

    // getters are not thread-safe
    bool get_mute();
    std::vector<SynthItem*> get_parents();
    // volume parameter getters
    double get_volume();
    bool get_volume_fixed();
    std::vector<int> get_volume_indexes();
    bool get_volume_scaled();
    double get_volume_scale_low();
    double get_volume_scale_high();
    double get_volume_scale_exponent();

    // generate a frame
    Frame process() override; // every sample
    void step() override; // every new data value (step)
    void control_process() override; // every process block

private:
    void retrieve_commands() override;
    void process_command(SynthItemCommand command) override;
    void process_add_child(SynthItem* child, PARAMETER parameter) override;
    void process_remove_child(SynthItem* child) override;
    void process_delete() override;

    void process_set_data(std::vector<double>* data,
                          std::vector<double>* mins,
                          std::vector<double>* maxes);
    void process_set_param_value(double val, PARAMETER param);
    void process_set_param_fixed(bool fixed, PARAMETER param);
    void process_set_param_indexes(std::vector<int> indexes, PARAMETER param);
    void process_set_param_scaled(bool scaled, PARAMETER param);
    void process_set_param_scale_low(double low, PARAMETER param);
    void process_set_param_scale_high(double high, PARAMETER param);
    void process_set_param_scale_exponent(double exponent, PARAMETER param);

    float calculate_volume_();

    ITEM my_type_;
    RingBuffer<SynthItemCommand> command_buffer_;
    SynthItemCommand current_command_;
    std::vector<SynthItem::PARAMETER> accepted_children_;
    std::vector<double>* data_;
    std::vector<double>* mins_;
    std::vector<double>* maxes_;
    std::vector<SynthItem*> parents_;
    std::vector<SynthItem*> inputs_;
    std::vector<SynthItem*> amods_;
    std::vector<int> volume_indexes_;
    bool muted_;

    // for scaling the data to intended volume values
    double volume_;
    bool volume_fixed_;
    bool volume_scaled_;
    double volume_low_;
    double volume_high_;
    double volume_exponent_;

};

} // namespace sow

#endif // VOLUME_H
