#include "sequencer.h"


namespace son {

Sequencer::Sequencer()
{
    paused = true;
    counter = 0;
    setSpeed(1);
    readyFlag = false;
    numRows = 0;

    //src init
    src_buf_idx = src_buf_max = 0;
    src_outData = new float[SRC_BUFSIZE]();
    src_inData = new float[SRC_BUFSIZE]();
    src_uData.buffer = new float[SRC_BUFSIZE]();
    src_type = SRC_LINEAR;
    src_uData.channels = 0;
    src_uData.inFrames = 64;
    src_cb = &src_callback;
    src_error = 0;
    src = NULL;

    //timer setup
    QThread* timerThread = new QThread;
    timer = new TimerWorker;
    connect(timer, SIGNAL(timeout()), this, SLOT(updateBuffers()));
    connect(this, SIGNAL(startTimer()), timer, SLOT(start()));
    connect(this, SIGNAL(stopTimer()), timer, SLOT(stop()));
    timer->moveToThread(timerThread);

}

bool Sequencer::enqueue(QVector<double> data)
{
    bool result = ringBuffer->push(data);
    return result;
}

void Sequencer::setRingBuffer(son::RingBuffer *buffer)
{
    ringBuffer = buffer;
}

void Sequencer::setLineView(LineView *view)
{
    lineView = view;
    src_uData.lineView = lineView;
}

long Sequencer::src_callback(void *cb_data, float **audio)
{
    QVector<double> col;
    long frameCount = 0;
    src_cb_data* uData = static_cast<src_cb_data*>(cb_data);

    col = uData->lineView->getCurrentColumn();

    for(int i = 0; i < uData->channels; ++i)
    {
        uData->buffer[i] = (float)(col[i]);
    }

    frameCount++;
    *audio = &(uData->buffer[0]);
    uData->lineView->advancePlayhead(frameCount);
    return frameCount;
}

void Sequencer::updateBuffers()
{
    if(ringBuffer->full() || paused)
    {
        return;
    }
    transferSamples();
}

void Sequencer::dimensionsChanged(int rowCount)
{
    if(numRows != rowCount)
    {
        numRows = rowCount;
        src_uData.channels = numRows;
        if(src)
        {
            src = src_delete(src);
        }
        src = src_init();
        if(!src)
        {
            qDebug() << "Could not init src: " << src_strerror(src_error);
        }
    }
}

void Sequencer::start()
{
    ringBuffer->reset();
    emit startTimer();
    paused = false;
    updateBuffers();
}

void Sequencer::stop()
{
    emit stopTimer();
    paused = true;
}

//UNUSED?!
void Sequencer::init(int channels)
{
    stop();

    if(numRows != channels)
    {
        numRows = channels;
        delete [] src_outData;
        src_outData = new float[numRows * SRC_BUFSIZE];
        src = src_init();
    }
}

int Sequencer::convertSamples()
{
    int samplesGenerated = 0;
    samplesGenerated = src_callback_read(src, 1, SRC_BUFSIZE, src_outData);
    if(src_error)
    {
        qDebug() << src_strerror(src_error);
    }
    qDebug() << "SRC frames: " << src_buf_max;
    return samplesGenerated;
}

void Sequencer::transferSamples()
{
    bool success;

    do
    {
        success = false;
        if(src_buf_idx > src_buf_max - 1)
        {
            src_buf_max = convertSamples();
            src_buf_idx = 0;
        }

        while(src_buf_idx < src_buf_max)
        {
            QVector<double> col;
            for(int i = 0; i < numRows; ++i)
            {
                col.push_back(src_outData[src_buf_idx * numRows + i]);
            }
            if((success = ringBuffer->push(col)))
            {
                src_buf_idx++;
            }
        }

    } while(success);
}

SRC_STATE* Sequencer::src_init()
{
    SRC_STATE* state;

    state = src_callback_new(src_cb,
                             src_type,
                             src_uData.channels,
                             &src_error,
                             &src_uData);
    if(src_error)
    {
        qDebug() << src_strerror(src_error);
    }
    return state;
}

void Sequencer::setSpeed(int stepsPerSec)
{
    src_ratio = 44100.0/stepsPerSec;
}

}
