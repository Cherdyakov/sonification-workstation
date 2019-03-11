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
    Q_INVOKABLE sow::QtSynthItem* createItem(SowEnums::ITEM type);
    Q_INVOKABLE virtual void addParent(QtSynthItem* parent) override;
    Q_INVOKABLE virtual void removeParent(QtSynthItem* parent) override;
    Q_INVOKABLE virtual bool addChild(QtSynthItem *child) override;
    Q_INVOKABLE virtual void removeChild(QtSynthItem *child) override;
    Q_INVOKABLE void deleteItem(QtSynthItem* item);
    // add or remove SynthItem from block processing
    Q_INVOKABLE void subscribeItem(QtSynthItem* item);
    void unsubscribe_item(QtSynthItem* item);


/*
 * From transport.h
 */
    // interface overrides
    void setData(QVector<double>* data,
                  QVector<double>* mins,
                  QVector<double>* maxes) override;

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

    void processCommand(SynthItemCommand command) override;

    void processSubscribeItem(QtSynthItem* item);
    void processUnsubscribeItem(QtSynthItem* item);

    void processSetDataset(Dataset *dataset);
    void processSetPlaybackPosition(double pos);

    void retrieveNextDataColumn();
    void calculateReturnPosition();
    QVector<double> interpolate(QVector<double> first, QVector<double> second, double mu);

    Frame frame_buffer_[4096];
    QVector<QtSynthItem*> subscribers_;
    Dataset* dataset_;
    QVector<double> current_data_column_;
    std::atomic<double> return_pos_;
    float master_volume_;
    unsigned int frame_rate_;
    unsigned int current_index_;
    double mu_;
    int speed_;
    double loop_begin_;
    double loop_end_;
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
