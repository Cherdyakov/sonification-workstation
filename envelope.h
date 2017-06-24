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

    enum class SEGMENT {
        ATTACK,
        DECAY
    };

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
    void process_set_param_scale_vals(double low,
                                      double high,
                                      double exp,
                                      PARAMETER param);

    unsigned int calculate_num_attack_frames();
    unsigned int calculate_num_decay_frames();
    float calculate_envelope_value();
    void advance_position();
    void reset();

    ITEM my_type_;
    RingBuffer<SynthItemCommand> command_buffer_;
    SynthItemCommand current_command_;
    std::vector<SynthItem::PARAMETER> accepted_children_;
    SEGMENT current_segment_;
    std::vector<double>* data_;
    std::vector<double>* mins_;
    std::vector<double>* maxes_;
    std::vector<SynthItem*> parents_;
    std::vector<SynthItem*> inputs_;
    std::vector<SynthItem*> amods_;
    std::vector<int> attack_indexes_;
    std::vector<int> decay_indexes_;
    bool muted_;

    // segment lengths and position in current segment
    unsigned int position_in_segment_;
    unsigned int num_attack_frames_;
    unsigned int num_decay_length_;
    float last_value_;
    float start_value_;
    float attack_delta_;
    bool done_;

    double attack_;
    bool attack_fixed_;
    // for scaling the data to intended values
    bool attack_scaled_;
    double attack_low_;
    double attack_high_;
    double attack_exponent_;

    double decay_;
    bool decay_fixed_;
    // for scaling the data to intended values
    bool decay_scaled_;
    double decay_low_;
    double decay_high_;
    double decay_exponent_;

};

} // son namespace

#endif // ENVELOPE_H
