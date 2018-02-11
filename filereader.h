#ifndef FILEREADER_H
#define FILEREADER_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QString>

#include "dataset.h"

class FileReader : public QObject
{
    Q_OBJECT

public:
    explicit FileReader(QObject *parent = 0);

private:
    void readCSV(QString filename, son::Dataset *dataset);

signals:
    void datasetChanged(son::Dataset *data);
    void qmlDatasetChanged(uint height, uint width);

public slots:
    void on_newDatafile(QString filename, son::Dataset *dataset);

private slots:

};

#endif // FILEREADER_H
