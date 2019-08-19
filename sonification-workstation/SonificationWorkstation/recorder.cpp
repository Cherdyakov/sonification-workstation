#include "recorder.h"
#include "constants.h"

#include <QtDebug>

namespace sow {

Recorder::Recorder(QObject *parent) : QObject(parent)
{
    connect(&copyTimer_, &QTimer::timeout,
            this, &Recorder::CopySamples);

}

void Recorder::Start()
{
    SF_INFO sfinfo = {0};
    sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
    sfinfo.channels = 1;
    sfinfo.samplerate = 44100;

    const char* path = "hello.wav";

    int bufferSize = 48000;
    float buffer[48000];

    SNDFILE * outfile = sf_open(path, SFM_WRITE, &sfinfo);
    qDebug() << sf_strerror(outfile);
    sf_count_t count = sf_write_float(outfile, &buffer[0], bufferSize) ;
    sf_write_sync(outfile);
    sf_close(outfile);
}

void Recorder::Stop()
{
//    copyTimer_.stop();
}

void Recorder::Write(Frame frame)
{
//    rec_.write(frame.left, frame.right);
}

void Recorder::CopySamples()
{
//    float* buf;

//    int n = rec_.read(buf);
//    qDebug() << sf_.write(buf, n);
}



}
