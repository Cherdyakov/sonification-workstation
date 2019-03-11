#ifndef QTTRANSPORT_H
#define QTTRANSPORT_H

#include <QObject>
#include <QTimer>
#include "qtsynthitem.h"
#include "qtoscillator.h"
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
    Q_INVOKABLE sow::QtSynthItem* createItem(ENUMS::ITEM_TYPE type);
    Q_INVOKABLE void deleteItem(QtSynthItem* item);
    // add or remove SynthItem from block processing
    Q_INVOKABLE void subscribe(QtSynthItem* item);
    Q_INVOKABLE void unsubscribe(QtSynthItem* item);

    float pos(); // for polling state from outside
    Frame process() override;       // every sample
    void controlProcess() override; // every process block

public slots:

    // slots for controlling playback
    void onDatasetchanged(sow::Dataset *dataset);
    void onPausechanged(bool p);
    void onPoschanged(float pos);
    void onSpeedchanged(float speed);
    void onLoopingchanged(bool looping);
    void onLoopPointsChanged(float begin, float end);
    void onInterpolateChanged(bool interpolate);

private:

    RingBuffer<TransportCommand> transportCommandBuffer_;
    Frame frameBuffer_[4096];
    QVector<QtSynthItem*> subscribers_;
    Dataset* dataset_;
    QVector<double> currentDataColumn_;
    std::atomic<float> returnPos_;
    float masterVolume_;
    unsigned int frameRate_;
    unsigned int currentIndex_;
    float mu_;
    int speed_;
    float loopBegin_;
    float loopEnd_;
    bool dataStale_;
    bool paused_;
    bool loop_;
    bool interpolate_;

    virtual void processDatasetCommand(DatasetCommand cmd) override;
    void processTransportCommand(TransportCommand cmd);
    void processSubscribeItem(QtSynthItem* item);
    void processUnsubscribeItem(QtSynthItem* item);
    void processDeleteItem(QtSynthItem* item);
    void processSetDataset(Dataset *dataset);
    void processSetPlaybackPosition(float pos);
    void retrieveNextDataColumn();
    void calculateReturnPosition();
    QVector<double> interpolate(QVector<double> first, QVector<double> second, double mu);

signals:
    void posChanged(double pos);

private slots:
    void updatePos();

};

} // Namespace sow.

#endif // QTTRANSPORT_H
