#ifndef SEQUENCER_H
#define SEQUENCER_H

#include <QObject>
#include <QThread>
#include <QVector>
#include <QDebug>
#include <QMutex>

#include "ringbuffer.h"
#include "samplerate.h"
#include "lineview.h"
#include "timerworker.h"

#define SRC_BLOCKSIZE 128
#define SRC_OUTSIZE 256

namespace son
{

//forward dec
class LineView;

typedef struct {
    LineView* lineView;
    int channels;
    long inFrames;
    float buffer[SRC_OUTSIZE];
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
    void start();
    void stop();

    std::atomic<bool> readyFlag;


private:

    RingBuffer* ringBuffer;
    LineView* lineView;
    QTimer* timer;


    QMutex ringBufferMutex;
    std::atomic<bool> paused;
    std::atomic<int> stepsPerSecond;
    std::atomic<int> ticksPerStep;
    int counter;
    int numRows;
    long resampleData(); //src on data columns
    void moveData(); //move converted data to the ringBuffer


    std::atomic<double> src_ratio;
    int src_buf_idx;
    int src_buf_max;
    SRC_STATE *src_init();
    long src_numFrames;
    int src_type;
    int src_error;
    SRC_STATE* src;
    src_cb_data src_uData;
    src_callback_t src_cb; //pointer to src_callback func
    float src_outData [SRC_OUTSIZE];

    static long src_input_callback(void* cb_data, float** audio); //src_callback func


private slots:
    void dimensionsChanged(int rowCount);

public slots:
    void fillRingBuffer();  
    void setSpeed(int stepsPerSec);

signals:

};

} // son namespace

#endif // SEQUENCER_H
