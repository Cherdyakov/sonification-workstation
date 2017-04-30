#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include <algorithm>

#include "Gamma/Oscillator.h"
#include "synthitem.h"
#include "ringbuffer.h"
#include "utility.h"

namespace son {

class Oscillator : public SynthItem
{

public:
    Oscillator();
    virtual ~Oscillator();
    void delete_item() override; // helper when deleting item contained in synth tree

    void set_data(std::vector<double>* data,
                  std::vector<double> mins,
                  std::vector<double> maxes) override;
    void add_parent(SynthItem* parent) override;
    void remove_parent(SynthItem* parent) override;
    bool add_child(SynthItem *child, PARAMETER parameter) override;
    void remove_child(SynthItem *item) override;

    void set_freq(double freq);
    void set_freq_indexes(std::vector<int> indexes);
    void set_freq_fixed(bool fixed);
    void set_freq_scaled(bool scaled);
    void set_freq_scale_vals(double low, double high, double exp);

    float process() override;

protected:
    void process_set_freq(double frequency_);
    void process_set_fixed_freq(bool frequency_fixed_);
    void process_set_freq_indexes(std::vector<int> indexes);
    void process_set_scale_freq(bool freq_scaled);
    void process_set_freq_scale_vals(double low, double high, double exp);

private:
    void process_command(SynthItemCommand command) override;
    void process_add_child(SynthItem* child, PARAMETER parameter) override;
    void process_remove_child(SynthItem* child) override;
    void process_add_parent(SynthItem* parent) override;
    void process_remove_parent(SynthItem* parent) override;

    void process_delete_item() override;

    void set_gen_freqs();

    ITEM my_type_;
    std::vector<gam::Sine<>> gens_;
    std::vector<SynthItem::PARAMETER> accepted_children_;
    SynthItemCommand current_command_;
    std::vector<double>* data_;
    std::vector<double> mins_;
    std::vector<double> maxes_;
    std::vector<SynthItem*> parents_;
    std::vector<SynthItem*> fmods_;
    std::vector<SynthItem*> amods_;
    std::vector<int> freq_indexes_;
    bool muted_;
    bool frequency_fixed_;
    double frequency_;

    //for scaling the data to intended frequency values
    bool freq_scaled;
    double freq_low_;
    double freq_high_;
    double freq_exponent;

};

} // namespace son

#endif // OSCILLATOR_H
