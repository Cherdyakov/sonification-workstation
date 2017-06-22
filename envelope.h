#ifndef ENVELOPE_H
#define ENVELOPE_H

#include "Gamma/Envelope.h"
#include "synthitem.h"
#include "ringbuffer.h"
#include "utility.h"

namespace son {

class Envelope final: public SynthItem
{
public:
    Envelope();
    ~Envelope();
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
    // attack parameter accessors
    void set_attack(double att);
    void set_attack_fixed(bool fixed);
    void set_attack_indexes(std::vector<int> indexes);
    void set_attack_scaled(bool scaled);
    void set_attack_scale_vals(double low, double high, double exp);
    // decay parameter accesors
    void set_decay(double dur);
    void set_decay_fixed(bool fixed);
    void set_decay_indexes(std::vector<int> indexes);
    void set_decay_scaled(bool scaled);
    void set_decay_scale_vals(double low, double high, double exp);
    // generate a frame
    Frame process() override;

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
    void process_set_param_scale_vals(double low,
                                      double high,
                                      double exp,
                                      PARAMETER param);

    double calculate_attack();
    double calculate_decay();
    void reset();

    ITEM my_type_;
    RingBuffer<SynthItemCommand> command_buffer_;
    SynthItemCommand current_command_;
    gam::AD<> env_;
    std::vector<SynthItem::PARAMETER> accepted_children_;
    std::vector<double>* data_;
    std::vector<double>* mins_;
    std::vector<double>* maxes_;
    std::vector<SynthItem*> parents_;
    std::vector<SynthItem*> inputs_;
    std::vector<SynthItem*> amods_;
    std::vector<int> attack_indexes_;
    std::vector<int> decay_indexes_;
    bool muted_;

    //for scaling the data to intended values
    double attack_;
    bool attack_fixed_;
    bool attack_scaled_;
    double attack_low_;
    double attack_high_;
    double attack_exponent_;

    double decay_;
    bool decay_fixed_;
    bool decay_scaled_;
    double decay_low_;
    double decay_high_;
    double decay_exponent_;

};

} // son namespace

#endif // ENVELOPE_H
