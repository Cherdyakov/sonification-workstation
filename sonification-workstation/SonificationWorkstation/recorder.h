#ifndef RECORDER_H
#define RECORDER_H

#include <QObject>
#include <QTimer>
#include <QMutex>
#include "Gamma/Recorder.h"
#include "Gamma/SoundFile.h"
#include "frame.h"

namespace sow {

class Recorder : public QObject
{
    Q_OBJECT
public:
    explicit Recorder(QObject *parent = nullptr);
    void Start(const QString path);
    void Stop();
    void Write(Frame frame);

private:
    gam::Recorder rec_;
    gam::SoundFile sf_;
    QTimer copyTimer_;
    QAtomicInt framesSinceCopy_;

private slots:

    void CopySamples();

};

} // Namespace sow.

#endif // RECORDER_H
