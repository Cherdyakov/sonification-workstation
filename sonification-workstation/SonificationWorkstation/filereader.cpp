#include "filereader.h"

FileReader::FileReader(QObject *parent) : QObject(parent) { }

QList<QStringList> FileReader::previewCSV(const QString filename)
{
    QList<QStringList> preview;
    QFile file(filename);
    if (!file.open(QFile::ReadOnly)) {
        qDebug() << file.errorString();
        return preview;
    }

    QTextStream inFile(&file);

    QList<QStringList> fileData;
    // Read the upper left 5x5 corner of the CSV for preevie
    while (!inFile.atEnd() && fileData.count() < 6) {
        QString line = inFile.readLine();
        fileData.append(line.split(","));
    }

    // Zero pad any short rows.
    int rows = fileData.count();
    int cols = 0;

    // Get number of columns in widest row.
    for(QStringList list : fileData)
    {
        if(list.count() > cols) cols = list.count();
    }

    // If csv is larger than 10 x 10, limit for the preview
    rows = rows > 10 ? 10 : rows;
    cols = cols > 10 ? 10 : cols;

    QList<QStringList>::iterator it;

    // Zero pad any short rows
    for(it = fileData.begin(); it != fileData.begin() + rows; it++)
    {
        while(it->count() < cols)
        {
            it->append("");
        }
    }

    for(int i = 0; i < rows; i++)
    {
        QStringList rowData;
        for (int j = 0; j < cols; j++)
        {
            rowData.append(fileData[i][j]);
        }
        preview.append(rowData);
    }

    return preview;
}

bool FileReader::readCSV(const QString filename, sow::Dataset * const dataset)
{
    QFile file(filename);
    if (!file.open(QFile::ReadOnly)) {
        qDebug() << file.errorString();
        return false;
    }

    QTextStream inFile(&file);

    QList<QStringList> fileData;
    while (!inFile.atEnd()) {
        QString line = inFile.readLine();
        fileData.append(line.split(","));
    }

    // Zero pad any short rows.
    int rows = fileData.count();
    int cols = 0;

    // Get number of columns in widest row.
    for(QStringList list : fileData)
    {
        if(list.count() > cols) cols = list.count();
    }

    QList<QStringList>::iterator it;

    for(it = fileData.begin(); it != fileData.end(); it++)
    {
        while(it->count() < cols)
        {
            it->append("0");
        }
    }

    std::vector<float> vec(static_cast<size_t>(rows*cols));
    size_t index = 0;

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
                qDebug() << "Substituting 0 for bad CSV value. row: "
                         << i << "col: " << j;
                vec[index++] = 0;
            }
        }
    }

    dataset->init(&vec, rows, cols);
    emit datasetChanged(dataset);
    emit qmlDatasetChanged(dataset->rows(), dataset->cols());
    return true;
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
