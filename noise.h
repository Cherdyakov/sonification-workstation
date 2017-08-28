#ifndef NOISE_H
#define NOISE_H

#include "utility.h"
#include "synthitem.h"
#include "Gamma/Noise.h"

namespace son {

class Noise : public SynthItem
{
public:
    Noise();

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
    // noise parameter accessors
    void set_noise(NOISE noise);

    // getters are not thread-safe
    bool get_mute();
    std::vector<SynthItem*> get_parents();
    // frequency parameter getters
    NOISE get_noise();

    // generate a frame
    Frame process() override; // every sample
    void step() override; // every new data value (step)
    void block_start() override; // every process block

private:
    void retrieve_commands() override;
    void process_command(SynthItemCommand command) override;
    void process_add_child(SynthItem* child, PARAMETER parameter) override;
    void process_remove_child(SynthItem* child) override;
    void process_delete() override;

    void process_set_data(std::vector<double>* data,
                          std::vector<double>* mins,
                          std::vector<double>* maxes);
    void process_set_noise(NOISE noise);

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
    bool muted_;

    gam::NoiseWhite<> white_;
    gam::NoisePink<> pink_;
    NOISE noise_type_;
};

} // namespace son

#endif // NOISE_H
