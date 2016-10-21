#ifndef FILEREADER_H
#define FILEREADER_H

#include <QObject>
#include <QFile>
#include <QDebug>
#include <QFileDialog>

class FileReader : public QObject
{
    Q_OBJECT
public:
    FileReader();

    void readCSV(QString filename);
    void writeCSV(QString filename);

};

#endif // FILEREADER_H
