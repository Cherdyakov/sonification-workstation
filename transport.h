#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <QObject>
#include <QTimer>
#include <QMutex>
#include "filereader.h"
#include "synthitem.h"
#include "oscillator.h"
//#include "qtaudifier.h"
//#include "qtmodulator.h"
//#include "qtpanner.h"
//#include "qtenvelope.h"
//#include "qtvolume.h"
//#include "qtnoise.h"
//#include "qtequalizer.h"

namespace sow {

class Transport : public SynthItem
{
    Q_OBJECT
public:

    explicit Transport(QObject *parent = nullptr);

    // factory for other SynthItems
    Q_INVOKABLE sow::SynthItem* createItem(ENUMS::ITEM_TYPE type);
    Q_INVOKABLE void deleteItem(SynthItem* item);
    // add or remove SynthItem from block processing
    Q_INVOKABLE void subscribe(SynthItem* item);
    Q_INVOKABLE void unsubscribe(SynthItem* item);

    float pos(); // for polling state from outside
    void loadDataset(QString file);
    Frame process() override;       // every sample
    void controlProcess() override; // every process block

private:

    RingBuffer<TransportCommand> transportCommandBuffer_;
    Frame frameBuffer_[4096];
    std::vector<SynthItem*> subscribers_;
    Dataset dataset_;
    QString filepath_;
    QMutex fileMutex_;
    std::vector<float> currentData_;
    std::vector<float> dataMinValues_;
    std::vector<float> dataMaxValues_;
    std::atomic<float> returnPos_;
    float masterVolume_;
    int frameRate_;
    int currentIndex_;
    float mu_;
    int speed_;
    float loopBegin_;
    float loopEnd_;
    bool dataStale_;
    bool pause_;
    bool loop_;
    bool interpolate_;

    void processTransportCommand(TransportCommand cmd);
    void processSubscribeItem(SynthItem* item);
    void processUnsubscribeItem(SynthItem* item);
    void processDeleteItem(SynthItem* item);
    void processImportDataset();
    void processSetPlaybackPosition(float pos);
    void refreshCurrentData();
    void calculateReturnPosition();
    std::vector<float> interpolate(std::vector<float> first, std::vector<float> second, float mu);

signals:
    void posChanged(float pos);
    void datasetImported(Dataset* dataset);

public slots:

    // slots for controlling playback
    void onImportDataset(QString file);
    void onPausechanged(bool p);
    void onPoschanged(float pos);
    void onSpeedchanged(float speed);
    void onLoopingchanged(bool looping);
    void onLoopPointsChanged(float begin, float end);
    void onInterpolateChanged(bool interpolate);

private slots:
    void updatePos();

};

} // Namespace sow.

#endif // TRANSPORT_H
