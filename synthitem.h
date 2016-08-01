#ifndef SYNTHITEM_H
#define SYNTHITEM_H

#include <QObject>

class synthItem : public QObject
{
    Q_OBJECT
public:
    explicit synthItem(QObject *parent = 0);

signals:

public slots:
};

#endif // SYNTHITEM_H