#ifndef DATAPROCESSOR_H
#define DATAPROCESSOR_H

#include <QObject>

class DataProcessor : public QObject
{
    Q_OBJECT
public:
    explicit DataProcessor(QObject *parent = nullptr);

signals:

};

#endif // DATAPROCESSOR_H
