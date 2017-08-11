#ifndef EQUALIZER_H
#define EQUALIZER_H

#include "Gamma/Filter.h"
#include "synthitem.h"

namespace son {

class Equalizer : public SynthItem
{
public:
    Equalizer();
    ~Equalizer();
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
    void remove_child(SynthItem *child) override;
    void mute(bool mute) override;
    // frequency parameter setters
    void set_frequency(double frequency);
    void set_frequency_fixed(bool fixed);
    void set_frequency_indexes(std::vector<int> indexes);
    void set_frequency_scaled(bool scaled);
    void set_frequency_scale_low(double low);
    void set_frequency_scale_high(double high);
    void set_frequency_scale_exponent(double exponent);

    // resonance parameter setters
    void set_resonance(double resonance);
    void set_resonance_fixed(bool fixed);
    void set_resonance_indexes(std::vector<int> indexes);
    void set_resonance_scaled(bool scaled);
    void set_resonance_scale_low(double low);
    void set_resonance_scale_high(double high);
    void set_resonance_scale_exponent(double exponent);

    // filter type
    void set_filter_type(FILTER_TYPE type);

    // getters are not thread-safe
    bool get_mute();
    std::vector<SynthItem*> get_parents();
    // frequency parameter getters
    double get_frequency();
    bool get_frequency_fixed();
    std::vector<int> get_frequency_indexes();
    bool get_frequency_scaled();
    double get_frequency_scale_low();
    double get_frequency_scale_high();
    double get_frequency_scale_exponent();
    // resonance parameter getters
    double get_resonance();
    bool get_resonance_fixed();
    std::vector<int> get_resonance_indexes();
    bool get_resonance_scaled();
    double get_resonance_scale_low();
    double get_resonance_scale_high();
    double get_resonance_scale_exponent();

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

    void process_set_filter_type(FILTER_TYPE type);

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
    std::vector<int> frequency_indexes_;
    std::vector<int> resonance_indexes_;
    bool muted_;

    // for scaling the data to intended frequency values
    double frequency_;
    bool frequency_fixed_;
    bool frequency_scaled_;
    double frequency_low_;
    double frequency_high_;
    double frequency_exponent_;

    // for scaling the data to intended resonance values
    double resonance_;
    bool resonance_fixed_;
    bool resonance_scaled_;
    double resonance_low_;
    double resonance_high_;
    double resonance_exponent_;

    // filter
    gam::Biquad<> filter_left_;
    gam::Biquad<> filter_right_;
    FILTER_TYPE filter_type_;
    gam::FilterType convert_filter_type(FILTER_TYPE type);
    void set_filter();
    double calculate_filter_frequency();
    double calculate_filter_resonance();

};

} // namespace son

#endif // EQUALIZER_H
