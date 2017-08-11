#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include <algorithm>

#include "Gamma/Oscillator.h"
#include "synthitem.h"
#include "ringbuffer.h"
#include "utility.h"

namespace son {

class Oscillator final: public SynthItem
{

public:
    Oscillator();
    ~Oscillator();
    // helper when deleting item contained in synth tree
    void delete_item() override;
    // interface overrides
    ITEM get_type() override;
    void set_data(std::vector<double>* data,
                  std::vector<double>* mins,
                  std::vector<double>* maxes) override;
    void add_parent(SynthItem* parent) override;
    void remove_parent(SynthItem* parent) override;
    bool add_child(SynthItem *child, PARAMETER param) override;
    void remove_child(SynthItem *item) override;
    void mute(bool mute) override;
    // frequency parameter setters
    void set_freq(double freq);
    void set_freq_fixed(bool fixed);
    void set_freq_indexes(std::vector<int> indexes);
    void set_freq_scaled(bool scaled);
    void set_freq_scale_low(double low);
    void set_freq_scale_high(double high);
    void set_freq_scale_exponent(double exponent);

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

    // generate a frame
    Frame process() override; // every sample
    void step() override; // every new data value (step)

private:
    void retrieve_commands() override;
    void process_command(SynthItemCommand command) override;
    void process_add_child(SynthItem* child, PARAMETER parameter) override;
    void process_remove_child(SynthItem* child) override;
    void process_delete_item() override;

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

    void set_gen_freqs();

    ITEM my_type_;
    RingBuffer<SynthItemCommand> command_buffer_;
    SynthItemCommand current_command_;
    std::vector<gam::Sine<>> gens_= std::vector<gam::Sine<>> (MAX_DIMENSIONS);
    std::vector<SynthItem::PARAMETER> accepted_children_;
    std::vector<double>* data_;
    std::vector<double>* mins_;
    std::vector<double>* maxes_;
    std::vector<SynthItem*> parents_;
    std::vector<SynthItem*> fmods_;
    std::vector<SynthItem*> amods_;
    std::vector<int> freq_indexes_;
    bool muted_;

    // for scaling the data to intended frequency values
    double freq_;
    bool freq_fixed_;
    bool freq_scaled_;
    double freq_low_;
    double freq_high_;
    double freq_exponent_;


};

} // namespace son

#endif // OSCILLATOR_H
