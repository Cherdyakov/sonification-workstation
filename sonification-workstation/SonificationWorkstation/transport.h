#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <QObject>
#include <QTimer>
#include <QMutex>
#include "filereader.h"
#include "synthitem.h"
#include "oscillator.h"
#include "amod.h"
#include "fmod.h"
#include "audifier.h"
#include "panner.h"
#include "volume.h"
#include "envelope.h"
#include "noise.h"
#include "equalizer.h"
#include "recorder.h"
#include "dataprocessorcontroller.h"

namespace sow {

class Transport : public SynthItem
{
    Q_OBJECT
public:

    explicit Transport(QObject *parent = nullptr, Dataset* dataset = nullptr, DataProcessorController* dataProcessorController = nullptr);

    // factory for other SynthItems
    Q_INVOKABLE sow::SynthItem* createItem(ENUMS::ITEM_TYPE type);
    Q_INVOKABLE void deleteItem(SynthItem* item);
    // add or remove SynthItem from block processing
    Q_INVOKABLE void subscribe(SynthItem* item);
    Q_INVOKABLE void unsubscribe(SynthItem* item);

    float pos(); // for polling state from outside
    Frame process() override;       // every sample
    void controlProcess() override; // every process block

private:

    RingBuffer<TransportCommand> transportCommandBuffer_;
    Frame frameBuffer_[4096];
    std::vector<SynthItem*> subscribers_;
    Recorder recorder_;
    Dataset* dataset_;
    DataProcessorController* dataProcessorController_;
    QString filepath_;
    QMutex fileMutex_;
    std::vector<float> currentData_;
    std::vector<float> dataMinValues_;
    std::vector<float> dataMaxValues_;
    std::atomic<float> returnPos_;
    float mainVolume_;
    float mainVolumeTarget_;
    int frameRate_;
    int currentIndex_;
    float mu_;
    float speed_;
    float loopBegin_;
    float loopEnd_;
    bool pause_;
    bool record_;
    bool loop_;
    bool importingDataset_;

    void processTransportCommand(TransportCommand cmd);
    void processSubscribeItem(SynthItem* item);
    void processUnsubscribeItem(SynthItem* item);
    void processDeleteItem(SynthItem* item);
    void processImportDataset();
    void processSetPlaybackPosition(float pos);
    void refreshCurrentData();
    void calculateReturnPosition();

signals:
    void posChanged(float pos);
    void datasetImportReady();

public slots:

    // slots for controlling playback and volume
    void onImportDataset(bool importing);
    void onPauseChanged(bool pause);
    void onRecordStart(QString path);
    void onRecordStop();
    void onPosChanged(float pos);
    void onSpeedChanged(float speed);
    void onLoopingChanged(bool looping);
    void onLoopPointsChanged(float begin, float end);
    void onMuteChanged(bool mute);
    void onMasterVolumeChanged(float vol);

private slots:
    void updatePos();

};

} // Namespace sow.

#endif // TRANSPORT_H
