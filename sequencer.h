#ifndef SEQUENCER_H
#define SEQUENCER_H

#include <QObject>
#include <QThread>
#include <QVector>
#include <QDebug>

#include "ringbuffer.h"
#include "samplerate.h"
#include "lineview.h"
#include "timerworker.h"

namespace son
{

//forward dec
class LineView;

typedef struct {
    LineView* lineView;
    int channels;
    long inFrames;
    float* buffer;
} src_cb_data;

class Sequencer : public QObject
{
    Q_OBJECT

public:
    Sequencer();

    bool enqueue(QVector<double> data);
    void setRingBuffer(RingBuffer* buffer);
    void setLineView(LineView* view);

    void setStepSize(int step);
    void setSpeed(int stepsPerSec);
    void start();
    void stop();
    void init(int ch);

    std::atomic<bool> readyFlag;


private:

    RingBuffer* ringBuffer;
    LineView* lineView;
    TimerWorker* timer;

    std::atomic<bool> paused;
    std::atomic<int> stepsPerSecond;
    std::atomic<int> ticksPerStep;
    int counter;
    int numRows;
    int convertSamples(); //src on data columns
    void transferSamples(); //move converted data to the ringBuffer


    std::atomic<double> src_ratio;
    const int SRC_BUFSIZE = 4096;
    int src_buf_idx;
    int src_buf_max;
    SRC_STATE *src_init();
    float* src_outData;
    float* src_inData;
    long src_numFrames;
    int src_type;
    int src_error;
    SRC_STATE* src;
    src_cb_data src_uData;
    src_callback_t src_cb; //pointer to src_callback func

    static long src_callback(void* cb_data, float** audio); //src_callback func


private slots:
    void updateBuffers();
    void dimensionsChanged(int rowCount);

signals:
    void startTimer();
    void stopTimer();

};

} // son namespace

#endif // SEQUENCER_H
