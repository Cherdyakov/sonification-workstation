#include "timerworker.h"

TimerWorker::TimerWorker(QObject *parent) : QObject(parent)
{
    timer = new QTimer;
    interval = 0;
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
}

void TimerWorker::update()
{
    emit timeout();
}

void TimerWorker::start()
{
    timer->setInterval(interval);
    timer->start();
}

void TimerWorker::stop()
{
    timer->stop();
}
