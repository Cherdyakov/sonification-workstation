#include "recorder.h"
#include "constants.h"

#include <QtDebug>

namespace sow {

Recorder::Recorder(QObject *parent) : QObject(parent)
{
    connect(&copyTimer_, &QTimer::timeout,
            this, &Recorder::CopySamples);

    framesSinceCopy_ = 0;
    rec_.resize(2, constants::SR * 2);
    sf_.channels(2);
    sf_.frameRate(constants::SR);
    sf_.format(gam::SoundFile::WAV);
}

void Recorder::Start(const QString path)
{
    sf_.path(path.toStdString());
    sf_.openWrite();

    copyTimer_.start();
}

void Recorder::Stop()
{
    copyTimer_.stop();
    sf_.close();
}

void Recorder::Write(Frame frame)
{
    rec_.write(frame.left, frame.right);
    framesSinceCopy_++;
}

void Recorder::CopySamples()
{
    if(framesSinceCopy_ > constants::SR)
    {
        framesSinceCopy_ = 0;
        float* buf;
        int n = rec_.read(buf);
        sf_.write(buf, n);
    }
}



}
