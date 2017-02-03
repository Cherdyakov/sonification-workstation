#ifndef TIMERWORKER_H
#define TIMERWORKER_H

#include <QObject>
#include <QTimer>

class TimerWorker : public QObject
{
    Q_OBJECT

public:
    explicit TimerWorker(QObject *parent = 0);

private:
    QTimer* timer;
    int interval;

signals:
    void timeout();

private slots:
    void update();

public slots:
    void start();
    void stop();
};

#endif // TIMERWORKER_H
