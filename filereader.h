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

    explicit FileReader(QObject *parent = nullptr);
    bool readCSV(const QString filename, sow::Dataset * const dataset);

signals:

    void datasetChanged(sow::Dataset * const data);
    void qmlDatasetChanged(const int rows, const int cols);

public slots:

    void on_newDatafile(const QString filename, sow::Dataset * const dataset);

};

#endif // FILEREADER_H
