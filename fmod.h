#ifndef FMOD_H
#define FMOD_H

#include <QObject>

class Fmod : public QObject
{
    Q_OBJECT
public:
    explicit Fmod(QObject *parent = nullptr);

signals:

public slots:
};

#endif // FMOD_H