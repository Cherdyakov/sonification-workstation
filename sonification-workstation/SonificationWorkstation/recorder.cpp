#include "recorder.h"
#include "constants.h"
#include <QtDebug>

namespace sow {

Recorder::Recorder(QObject *parent) : QObject(parent)
{
    connect(&copyTimer_, &QTimer::timeout,
            this, &Recorder::CopySamples);

    framesSinceCopy_ = 0;
    // Record buffer is two seconds long.
    rec_.resize(2, constants::SR * 2);
    // Record stereo WAVE, at application sample rate.
    sf_.channels(2);
    sf_.frameRate(constants::SR);
    sf_.format(gam::SoundFile::WAV);
}

void Recorder::Start(const QString path)
{
    // Open a .wav file for writing at the provided path.
    sf_.path(path.toStdString());
    sf_.openWrite();
    // Start regularly writing buffered samples to the file.
    copyTimer_.start();
}

void Recorder::Stop()
{
    copyTimer_.stop();
    // Write any remaining buffered samples to disk.
    float* buf;
    int n = rec_.read(buf);
    sf_.write(buf, n);
    // Close the soundfile.
    sf_.close();
}

void Recorder::Write(Frame frame)
{
    // For audio thread to write frames to the record buffer.
    rec_.write(frame.left, frame.right);
    framesSinceCopy_++;
}

void Recorder::CopySamples()
{
    // Every second, write buffered samples to disk.
    if(framesSinceCopy_ > constants::SR)
    {
        framesSinceCopy_ = 0;
        float* buf;
        int n = rec_.read(buf);
        sf_.write(buf, n);
    }
}



}
