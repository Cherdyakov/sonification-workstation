#ifndef SYNTHGRAPH_H
#define SYNTHGRAPH_H

#include <atomic>
#include <mutex>

#include "oscillator.h"
#include "audifier.h"
#include "modulator.h"
#include "panner.h"
#include "envelope.h"
#include "volume.h"
#include "ringbuffer.h"

namespace son {

class Transport final: public SynthItem
{

public:

    explicit Transport();
    virtual ~Transport();
    // interface overrides
    void delete_item() override;
    SynthItem::ITEM get_type();
    void set_data(std::vector<double>* data,
                  std::vector<double>* mins,
                  std::vector<double>* maxes) override;
    void add_parent(SynthItem* parent) override;
    void remove_parent(SynthItem* parent) override;
    bool add_child(SynthItem *child, PARAMETER param) override;
    void remove_child(SynthItem *child) override;
    void mute(bool mute) override;
    // for setting the entire dataset to be sonified
    void set_dataset(std::vector<double>* dataset, unsigned int height, unsigned int width);
    // functions for controlling playback
    void pause(bool pause);
    void set_playback_position(double pos);
    void set_speed(double speed_);
    void set_looping(bool loop_);
    void set_loop_points(double begin, double end);
    void set_interpolate(bool interpolate_);
    // factory for other SynthItems (probably should do something else)
    SynthItem *create_item(SynthItem::ITEM type);
    // for polling state from outside
    double get_playback_position();
    // generate a frame
    Frame process() override; // every sample
    void step() override; // every new data value (step)

private:
    void retrieve_commands() override;
    void process_command(SynthItemCommand command) override;
    void process_add_child(SynthItem* child, PARAMETER parameter) override;
    void process_remove_child(SynthItem* child) override;
    void process_delete_item() override;

    void process_set_dataset(std::vector<double>*dataset,
                             unsigned int height,
                             unsigned int width);
    void process_set_playback_position(double pos);
    void process_set_interpolate(bool interpolate_);

    void retrieve_next_data_column();
    void calculate_return_position();
    void calculate_min_max();

    ITEM my_type_;
    RingBuffer<SynthItemCommand> command_buffer_;
    SynthItemCommand current_command_;
    std::vector<SynthItem::PARAMETER> accepted_children_;
    std::vector<double>* dataset_;
    std::vector<double> current_data_column_;
    std::vector<double> min_data_vals_;
    std::vector<double> max_data_vals_;
    std::atomic<double> return_pos;
    std::vector<SynthItem*> inputs_;
    std::vector<SynthItem*> amods_;
    float master_volume_;
    unsigned int block_size_;
    unsigned int data_height_;
    unsigned int data_width_;
    unsigned int frame_rate;
    unsigned int current_index_;
    double mu_;
    double speed_;
    double loop_begin_;
    double loop_end_;
    bool muted_;
    bool data_stale_;
    bool paused_;
    bool loop_;
    bool interpolate_;

};

} // namespace son

#endif // SYNTHGRAPH_H
