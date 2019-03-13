#include "filereader.h"

FileReader::FileReader(QObject *parent) : QObject(parent) { }

void FileReader::readCSV(const QString filename, sow::Dataset * const dataset)
{
    QVector<float> vec;

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

    int rows = readData.count();  // == rows in CSV
    int cols = readData[0].count(); // == columns in CSV

    // Check if rows are of equal length
    bool unEven = false;
    for(QStringList list : readData)
    {
        int currentCount = static_cast<int>(list.count());
        if(currentCount != cols)
        {
            unEven = true;
            if(cols < currentCount)
            {
                cols = currentCount;
            }
        }
    }
    // Some rows were shorter than others
    // force data to have equal cols rows
    if(unEven)
    {
        for(int i = 0; i < rows; i++)
        {
            QStringList* list = &readData[static_cast<int>(i)];
            int currentCount = static_cast<int>(list->count());

            if(currentCount < cols)
            {
                qDebug() << "Row " << i << "is too short.  Padding with 0";
                while(currentCount < cols)
                {
                    list->append("0");
                    currentCount++;
                }
            }
        }
    }

    vec.resize(static_cast<int>(rows)*static_cast<int>(cols));
    int index = 0;

    for(int i = 0; i < rows; i++)
    {
        QStringList rowData = readData[static_cast<int>(i)];
        for (int j = 0; j < cols; j++)
        {
            bool isFloat = false;
            QString temp = rowData[static_cast<int>(j)];
            float value = temp.toFloat(&isFloat);
            if(isFloat)
            {
                vec[index++] = value;
            }
            else
            {
                qDebug() << "FileReader: bad value. row: "
                         << i << "col: " << j;
                vec[index++] = 0;
            }
        }
    }

    dataset->init(vec, rows, cols);
    emit datasetChanged(dataset);
    emit qmlDatasetChanged(dataset->rows(), dataset->cols());
}

void FileReader::on_newDatafile(const QString filename, sow::Dataset * const dataset)
{
    // clear the dataset
    if(filename.isEmpty()) {
        dataset->clear();
        datasetChanged(dataset);
    }
    readCSV(filename, dataset);
}
