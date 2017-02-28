#ifndef FILEREADER_H
#define FILEREADER_H

#include <QObject>
#include <QDebug>

#include "qtcsv/reader.h"

class FileReader : public QObject
{
    Q_OBJECT

public:
    explicit FileReader(QObject *parent = 0);
    void readCSV(QString filename, std::vector<double>* array);

private:

signals:
    void datasetChanged(std::vector<double>* data, uint height, uint width);
    void qmlDatasetChanged(uint height, uint width);

private slots:

};

#endif // FILEREADER_H
