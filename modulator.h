#ifndef MODULATOR_H
#define MODULATOR_H

#include "oscillator.h"

namespace son {

class Modulator final: public SynthItem
{
public:
    Modulator();
    // helper when deleting item contained in synth tree
    void delete_item() override;
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
    void set_freq_scale_vals(double low, double high, double exp);
    // depth parameter accessors
    void set_mod_type(PARAMETER param);
    void set_depth(double depth);
    void set_depth_fixed(bool fixed);
    void set_depth_indexes(std::vector<int> indexes);
    void set_depth_scaled(bool scaled);
    void set_depth_scale_vals(double low, double high, double exp);
    // generate a frame
    Frame process() override;

private:
    void retrieve_commands() override;
    void process_command(SynthItemCommand command) override;
    void process_add_child(SynthItem* child, PARAMETER parameter) override;
    void process_remove_child(SynthItem* child) override;
    void process_delete_item() override;

    void process_set_data(std::vector<double>* data, std::vector<double> *mins, std::vector<double> *maxes);
    void process_set_mod_type(PARAMETER param);
    void process_set_param_value(double val, PARAMETER param);
    void process_set_param_fixed(bool fixed, PARAMETER param);
    void process_set_param_indexes(std::vector<int> indexes, PARAMETER param);
    void process_set_param_scaled(bool scaled, PARAMETER param);
    void process_set_param_scale_vals(double low, double high, double exp, PARAMETER param);

    void set_gen_freq();
    float get_depth_value();

    ITEM my_type_;
    PARAMETER mod_type_;
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
