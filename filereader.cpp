#include "filereader.h"

FileReader::FileReader(QObject *parent) : QObject(parent) { }

void FileReader::readCSV(const QString filename, sow::Dataset * const dataset)
{
    std::vector<float> vec;

    QFile file(filename);
    if (!file.open(QFile::ReadOnly)) {
        qDebug() << file.errorString();
        return;
    }

    QTextStream inFile(&file);

    QList<QStringList> fileData;
    while (!inFile.atEnd()) {
        QString line = inFile.readLine();
        fileData.append(line.split(","));
    }
    int rows = fileData.count();  // == rows in CSV
    int cols = fileData[0].count(); // == columns in CSV


    ///
    ///
    ///
    // TODO: Should be checking cols for even now, not rows
    ///
    ///
    ///
    // Check if rows are of equal length
 /*   bool unEven = false;
    for(QStringList list : readData)
    {
        uint currentCount = static_cast<uint>(list.count());
        if(currentCount != width)
        {
            unEven = true;
            if(width < currentCount)
            {
                width = currentCount;
            }
        }
    }
    // Some rows were shorter than others
    // force data to have equal width rows
    if(unEven)
    {
        for(uint i = 0; i < height; i++)
        {
            QStringList* list = &readData[static_cast<int>(i)];
            uint currentCount = static_cast<uint>(list->count());

            if(currentCount < width)
            {
                qDebug() << "Row " << i << "is too short.  Padding with 0";
                while(currentCount < width)
                {
                    list->append("0");
                    currentCount++;
                }
            }
        }
} */

    vec.resize(rows*cols);
    int index = 0;

    for(int i = 0; i < rows; i++)
    {
        QStringList rowData = fileData[i];
        for (int j = 0; j < cols; j++)
        {
            bool isFloat = false;
            QString temp = rowData[j];
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
