#ifndef QTTRANSPORT_H
#define QTTRANSPORT_H

#include <QObject>
#include <QTimer>
#include "qtsynthitem.h"
#include "qtoscillator.h"
//#include "transport.h"
//#include "qtaudifier.h"
//#include "qtmodulator.h"
//#include "qtpanner.h"
//#include "qtenvelope.h"
//#include "qtvolume.h"
//#include "qtnoise.h"
//#include "qtequalizer.h"

namespace sow {

class QtTransport : public QtSynthItem
{
    Q_OBJECT
public:

    explicit QtTransport(QObject *parent = nullptr);

    // factory for other SynthItems
    Q_INVOKABLE QtSynthItem* createItem(ITEM type);
    Q_INVOKABLE virtual ITEM getType() override;
    Q_INVOKABLE virtual void deleteSelf() override;
    Q_INVOKABLE virtual void addParent(QtSynthItem* parent) override;
    Q_INVOKABLE virtual void removeParent(QtSynthItem* parent) override;
    Q_INVOKABLE virtual bool addChild(QtSynthItem *child, PARAMETER param) override;
    Q_INVOKABLE virtual void removeChild(QtSynthItem *child) override;
    Q_INVOKABLE virtual void mute(bool mute) override;
    Q_INVOKABLE void deleteItem(QtSynthItem* item);
    // add or remove SynthItem from block processing
    Q_INVOKABLE void subscribeItem(QtSynthItem* item);
    void unsubscribe_item(QtSynthItem* item);


/*
 * From transport.h
 */
    // interface overrides
    void setData(std::vector<double>* data,
                  std::vector<double>* mins,
                  std::vector<double>* maxes) override;

    // for setting the entire dataset to be sonified
    void set_dataset(Dataset* dataset);
    // functions for controlling playback
    void pause(bool pause);
    void set_playback_position(double pos);
    void set_speed(int speed_);
    void set_looping(bool loop_);
    void set_loop_points(double begin, double end);
    void set_interpolate(bool interpolate_);
    // for polling state from outside
    double get_playback_position();
    // generate frame
    Frame process() override; // every sample
    void step() override; // every new data value (step)
    void controlProcess() override; // every process block

    // getters are not thread safe
    bool getMute() override;
    std::vector<QtSynthItem*> getParents() override;



public slots:

    // slots for controlling playback
    void on_datasetChanged(sow::Dataset *dataset);
    void on_pausedChanged(bool p);
    void on_posChanged(double pos);
    void on_speedChanged(int speed);
    void on_loopingChanged(bool looping);
    void on_loopPointsChanged(double begin, double end);
    void on_interpolateChanged(bool interpolate);

    // for polling state from outside
    // (i.e. GUI)
    double getPos();

private:
    void retrieveCommands() override;
    void processCommand(SynthItemCommand command) override;
    void processAddChild(QtSynthItem* child, PARAMETER parameter) override;
    void processRemoveChild(QtSynthItem* child) override;
    void processDelete() override;
    void process_delete_item(QtSynthItem* item);

    void process_subscribe_item(QtSynthItem* item);
    void process_unsubscribe_item(QtSynthItem* item);

    void process_set_dataset(Dataset *dataset);
    void process_set_playback_position(double pos);

    void retrieve_next_data_column();
    void calculate_return_position();
    std::vector<double> interpolate(std::vector<double> first, std::vector<double> second, double mu);

    ITEM my_type_;
    PARAMETER my_child_type_;
    RingBuffer<SynthItemCommand> command_buffer_;
    SynthItemCommand current_command_;
    Frame frame_buffer_[4096];
    std::vector<QtSynthItem*> subscribers_;
    std::vector<PARAMETER> accepted_children_;
    Dataset* dataset_;
    std::vector<double> current_data_column_;
    std::vector<double> mins_;
    std::vector<double> maxes_;
    std::atomic<double> return_pos_;
    std::vector<QtSynthItem*> inputs_;
    std::vector<QtSynthItem*> amods_;
    float master_volume_;
    unsigned int frame_rate_;
    unsigned int current_index_;
    double mu_;
    int speed_;
    double loop_begin_;
    double loop_end_;
    bool muted_;
    bool data_stale_;
    bool paused_;
    bool loop_;
    bool interpolate_;



signals:
    void posChanged(double pos);

private slots:
    void updatePos();

};

} // Namespace sow.

#endif // QTTRANSPORT_H
