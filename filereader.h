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
    QList<int> readCSV(QString filename, std::vector<double>* array);
    QList<int> readJSON(QString filename, std::vector<double>* array);

private:

signals:
    void dataDimensionsChanged(int h, int w, int d);

public slots:
};

#endif // FILEREADER_H
