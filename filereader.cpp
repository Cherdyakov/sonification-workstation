#include "filereader.h"

FileReader::FileReader(QObject *parent) : QObject(parent)
{

}

QList<int> FileReader::readCSV(QString filename, std::vector<double> *array)
{

    QList<QStringList> readData = QtCSV::Reader::readToList(filename);

    int height = readData[0].count();   // == rows in CSV
    int width = readData.count();       // == columns in CSV

    for(int i = 0; i < readData.count(); i++)
    {
        QStringList rowData = readData[i];
        for (int j = 0; j < rowData.count(); j++)
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
                array->clear();
                height = width = 0;
            }
        }
    }

    return QList<int>({height, width});
}

QList<int> FileReader::readJSON(QString filename, std::vector<double> *array)
{
    Q_UNUSED(filename);
    Q_UNUSED(array);
    qDebug() << "JSON import not implemented";
}
