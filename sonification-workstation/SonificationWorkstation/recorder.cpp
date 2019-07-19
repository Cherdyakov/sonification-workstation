#include "recorder.h"
#include "constants.h"

#include <QtDebug>

namespace sow {

Recorder::Recorder(QObject *parent) : QObject(parent)
{
    connect(&copyTimer_, &QTimer::timeout,
            this, &Recorder::CopySamples);

    rec_.resize(2, 8192);
}

void Recorder::Start()
{
    sf_.channels(2);
    sf_.frameRate(constants::SR);
    sf_.format(gam::SoundFile::AIFF);
    sf_.path("output.wav");
    sf_.openWrite();

    copyTimer_.start(10);
}

void Recorder::Stop()
{
    copyTimer_.stop();
        sf_.close();
}

void Recorder::Write(Frame frame)
{
    rec_.write(frame.left, frame.right);
}

void Recorder::CopySamples()
{
    float* buf;
    int n = rec_.read(buf);
    qDebug() << sf_.write(buf, n);
}



}
