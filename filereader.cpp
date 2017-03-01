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

    QList<QStringList> readData = QtCSV::Reader::readToList(filename);

    uint height = readData.count();   // == rows in CSV
    uint width = readData[0].count(); // == columns in CSV

    for(uint i = 0; i < height; i++)
    {
        QStringList rowData = readData[i];
        for (uint j = 0; j < width; j++)
        {
            QString temp = rowData[j];
            bool isDouble = false;
            double value = temp.toDouble(&isDouble);
            if(isDouble)
            {
                array->push_back(value);
            }
            else
            {
                qDebug() << "FileReader: CSV import failed, bad value: " << temp;
                height = width = 0;
            }
        }
    }

    qDebug() << "Done reading file: " << QTime::currentTime();

    emit datasetChanged(array,height, width);
    emit qmlDatasetChanged(height, width);
}
