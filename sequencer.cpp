#include "sequencer.h"


namespace son {

Sequencer::Sequencer()
{
    paused = true;
    counter = 0;
    setSpeed(1);
    readyFlag = false;
    numRows = 0;

    //src related
    src = NULL;
    src_uData = NULL;
    src_writeBuffer = NULL;
    src_buf_idx = src_buf_max = 0;
    src_type = SRC_ZERO_ORDER_HOLD;
    src_cb = &src_input_callback;

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
}


void Sequencer::src_init()
{
    //create new uData for src
    if(src_uData)
    {
        delete[] src_uData->writeBuffer;
        delete src_uData;
    }
    //initialize uData for current numRows
    src_uData = new src_cb_data;
    src_uData->lineView = lineView;
    src_uData->channels = numRows;
    src_uData->src_error = 0;
    src_uData->framesToWrite = SRC_OUTFRAMES;
    src_uData->writeBuffer = new float[SRC_OUTFRAMES * 4 * numRows]();

    src = src_callback_new(src_cb,
                           src_type,
                           src_uData->channels,
                           &src_uData->src_error,
                           src_uData);

    if(!src)
    {
        qDebug() << "Could not init src: " << src_strerror(src_uData->src_error);
    }
    if(src_uData->src_error)
    {
        qDebug() << src_strerror(src_uData->src_error);
    }

    //reallocate src_writeBuffer
    if(src_writeBuffer)
    {
        delete[] src_writeBuffer;
    }
    src_writeBuffer = new float[2048]();
}

void Sequencer::dimensionsChanged(int rowCount)
{
    if(numRows != rowCount)
    {
        numRows = rowCount;
        src_init();
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
    //    src_ratio = 128.0;
}

void Sequencer::fillRingBuffer()
{
    if(ringBuffer->full() || paused)
    {
        return;
    }
//    if(src_buf_idx > src_buf_max - 1)
//    {
//        src_buf_idx = 0;
//        src_buf_max = resampleData();
//    }
    moveData();
}

void Sequencer::moveData()
{
    QVector<double> col = lineView->getCurrentColumn();
    bool success = ringBuffer->push(col);

    if(success)
    {
        lineView->advancePlayhead(1);
    }

//    while(src_buf_idx < src_buf_max && !ringBuffer->full())
//    {
//        QVector<double> col;
//        for(int i = 0; i < numRows; ++i)
//        {
//            col.push_back(src_uData->writeBuffer[src_buf_idx * numRows + i]);
//        }
//        if((ringBuffer->push(col)))
//        {
//            src_buf_idx += numRows;
//        }
//    }
}

long Sequencer::resampleData()
{
    long samplesGenerated = 0;
    samplesGenerated = src_callback_read(src,
                                         1,//src_ratio fails > 256
                                         src_uData->framesToWrite,
                                         src_writeBuffer);
    if(src_uData->src_error)
    {
        qDebug() << src_strerror(src_uData->src_error);
    }
    return samplesGenerated;
}

long Sequencer::src_input_callback(void *cb_data, float **audio)
{
    QVector<double> col;
    long colsRead = 0;
    src_cb_data* uData = static_cast<src_cb_data*>(cb_data);
    *audio = &(uData->writeBuffer[0]);

    for(int frame = 0; frame < uData->framesToWrite; ++frame)
    {
        col = uData->lineView->getCurrentColumn();

        for(int channel = 0; channel < uData->channels; ++channel)
        {
            uData->writeBuffer[frame * uData->channels + channel] = (float)(col[channel]);
        }
        colsRead++;
        uData->lineView->advancePlayhead(colsRead);
    }

    return colsRead;
}

}
