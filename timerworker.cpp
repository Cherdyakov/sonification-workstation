#include "timerworker.h"
#include <QDebug>

TimerWorker::TimerWorker(QObject *parent) : QObject(parent)
{
    timer = new QTimer;
    interval = 0;
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
}

void TimerWorker::update()
{
    qDebug() << "timeout";
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
