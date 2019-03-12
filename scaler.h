#ifndef SCALER_H
#define SCALER_H

#include <QObject>

class Scaler : public QObject
{
    Q_OBJECT
public:
    explicit Scaler(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SCALER_H