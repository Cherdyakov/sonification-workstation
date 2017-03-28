#include "filereader.h"
#include <QTime>

FileReader::FileReader(QObject *parent) : QObject(parent)
{

}

void FileReader::readCSV(QString filename, std::vector<double> *array)
{
    qDebug() << "Reading file: " << QTime::currentTime();

    if(array->size() > 0) {
        array->clear();
    }

    QFile file(filename);
    if (!file.open(QFile::ReadOnly)) {
        qDebug() << file.errorString();
        return;
    }

    QTextStream inFile(&file);

    QList<QStringList> readData;
        while (!inFile.atEnd()) {
            QString line = inFile.readLine();
            readData.append(line.split(","));
        }

    uint height = static_cast<uint>(readData.count());   // == rows in CSV
    uint width = static_cast<uint>(readData[0].count()); // == columns in CSV

    array->resize(width*height);
    uint index = 0;

    for(uint i = 0; i < height; i++)
    {
        QStringList rowData = readData[static_cast<int>(i)];
        for (uint j = 0; j < width; j++)
        {
            bool isDouble = false;
            QString temp = rowData[static_cast<int>(j)];
            double value = temp.toDouble(&isDouble);
            if(isDouble)
            {
                array->at(index++) = value;
            }
            else
            {
                qDebug() << "FileReader: bad value. row: "
                         << i << "col: " << j;
                array->at(index++) = 0;
            }
        }
    }

    qDebug() << "Done reading file: " << QTime::currentTime();

    emit datasetChanged(array,height, width);
    emit qmlDatasetChanged(height, width);
}
