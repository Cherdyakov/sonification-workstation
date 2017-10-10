#ifndef MODULATOR_H
#define MODULATOR_H

#include "oscillator.h"

namespace son {

class Modulator final: public SynthItem
{
public:
    Modulator();
    // helper when deleting item contained in synth tree
    void delete_self() override;
    // interface overrides
    ITEM get_type() override;
    void set_data(std::vector<double>* data, std::vector<double>* mins, std::vector<double>* maxes) override;
    void add_parent(SynthItem* parent) override;
    void remove_parent(SynthItem* parent) override;
    bool add_child(SynthItem *child, PARAMETER param) override;
    void remove_child(SynthItem *item) override;
    void mute(bool mute) override;
    // frequency parameter accessors
    void set_freq(double freq);
    void set_freq_fixed(bool fixed);
    void set_freq_indexes(std::vector<int> indexes);
    void set_freq_scaled(bool scaled);
    void set_freq_scale_low(double low);
    void set_freq_scale_high(double high);
    void set_freq_scale_exponent(double exponent);
    // depth parameter accessors
    void set_mod_type(PARAMETER param);
    void set_depth(double depth);
    void set_depth_fixed(bool fixed);
    void set_depth_indexes(std::vector<int> indexes);
    void set_depth_scaled(bool scaled);
    void set_depth_scale_low(double low);
    void set_depth_scale_high(double high);
    void set_depth_scale_exponent(double exponent);

    // getters are not thread-safe
    bool get_mute();
    std::vector<SynthItem*> get_parents();
    // frequency parameter getters
    double get_freq();
    bool get_freq_fixed();
    std::vector<int> get_freq_indexes();
    bool get_freq_scaled();
    double get_freq_scale_low();
    double get_freq_scale_high();
    double get_freq_scale_exponent();

    // depth parameter getters
    double get_depth();
    bool get_depth_fixed();
    std::vector<int> get_depth_indexes();
    bool get_depth_scaled();
    double get_depth_scale_low();
    double get_depth_scale_high();
    double get_depth_scale_exponent();

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

    void process_set_data(std::vector<double>* data, std::vector<double> *mins, std::vector<double> *maxes);
    void process_set_mod_type(PARAMETER param);
    void process_set_param_value(double val, PARAMETER param);
    void process_set_param_fixed(bool fixed, PARAMETER param);
    void process_set_param_indexes(std::vector<int> indexes, PARAMETER param);
    void process_set_param_scaled(bool scaled, PARAMETER param);
    void process_set_param_scale_low(double low, PARAMETER param);
    void process_set_param_scale_high(double high, PARAMETER param);
    void process_set_param_scale_exponent(double exponent, PARAMETER param);

    void set_gen_freq();
    float get_depth_value();

    ITEM my_type_;
    PARAMETER child_type_;
    RingBuffer<SynthItemCommand> command_buffer_;
    SynthItemCommand current_command_;
    gam::Sine<> gen_;
    std::vector<SynthItem::PARAMETER> accepted_children_;
    std::vector<double>* data_;
    std::vector<double>* mins_;
    std::vector<double>* maxes_;
    std::vector<SynthItem*> parents_;
    std::vector<SynthItem*> fmods_;
    std::vector<SynthItem*> amods_;
    std::vector<int> freq_indexes_;
    std::vector<int> depth_indexes_;
    bool muted_;

    // frequency
    double freq_;
    bool freq_fixed_;
    bool freq_scaled_;
    double freq_low_;
    double freq_high_;
    double freq_exponent_;

    // depth
    double depth_;
    bool depth_fixed_;
    bool depth_scaled_;
    double depth_low_;
    double depth_high_;
    double depth_exponent_;

};

} // namespace son

#endif // MODULATOR_H
