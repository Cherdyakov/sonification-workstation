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
    src_type = SRC_ZERO_ORDER_HOLD;
    src_uData.channels = 0;
    src_uData.inFrames = 64;
    src_cb = &src_input_callback;
    src_error = 0;
    src = NULL;

    //buffering timer
    timer = new QTimer;
    timer->setInterval(0);
    connect(timer, SIGNAL(timeout()), this, SLOT(fillRingBuffer()));
    timer->start();

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
    paused = false;
}

void Sequencer::stop()
{
    paused = true;
}

void Sequencer::setSpeed(int stepsPerSec)
{
    src_ratio = 44100.0/(double)stepsPerSec;
}

void Sequencer::fillRingBuffer()
{
//    ringBufferMutex.tryLock();

    if(ringBuffer->full() || paused)
    {
        return;
    }
    moveData();

//    ringBufferMutex.unlock();
}

void Sequencer::moveData()
{

    if(src_buf_idx > src_buf_max - 1)
    {
        src_buf_idx = 0;
        src_buf_max = resampleData();
    }

    while(src_buf_idx < src_buf_max && !ringBuffer->full())
    {
        QVector<double> col;
        for(int i = 0; i < numRows; ++i)
        {
            col.push_back(src_outData[src_buf_idx * numRows + i]);
        }
        if((ringBuffer->push(col)))
        {
            src_buf_idx += numRows;
        }
    }
}

long Sequencer::resampleData()
{
    long samplesGenerated = 0;
    samplesGenerated = src_callback_read(src, src_ratio, SRC_BLOCKSIZE, src_outData);
    if(src_error)
    {
        qDebug() << src_strerror(src_error);
    }
    return samplesGenerated;
}

long Sequencer::src_input_callback(void *cb_data, float **audio)
{
    QVector<double> col;
    long colsRead = 0;
    src_cb_data* uData = static_cast<src_cb_data*>(cb_data);

    col = uData->lineView->getCurrentColumn();

    for(int i = 0; i < uData->channels; ++i)
    {
        uData->buffer[i] = (float)(col[i]);
    }

    colsRead++;
    *audio = &(uData->buffer[0]);
    uData->lineView->advancePlayhead(colsRead);
    return colsRead;
}

}
