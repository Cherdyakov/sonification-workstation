#ifndef FILTER_H
#define FILTER_H

#include <QObject>

class filter : public QObject
{
    Q_OBJECT
public:
    explicit filter(QObject *parent = nullptr);

signals:

};

#endif // FILTER_H
