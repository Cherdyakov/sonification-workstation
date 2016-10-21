#include "filereader.h"

FileReader::FileReader()
{

}

void FileReader::readCSV(QString fileName)
{
    QString data;
    QFile importedCSV(fileName);
    QStringList rowOfData;
    QStringList rowData;
    data.clear();
    rowOfData.clear();
    rowData.clear();
    if (!importedCSV.open(QFile::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error opening csv file.";
        return;
    }

    data = importedCSV.readAll();
    rowOfData = data.split("\n");
    importedCSV.close();

    for (int x = 0; x < rowOfData.size(); x++)
    {
        rowData = rowOfData.at(x).split(",");
        for (int y = 0; y < rowData.size(); y++)
        {
//            ui->tableWidgetInjectionLocationsExpandedDialog->item(x,y)->setText(rowData[y]);
        }
    }
}

void FileReader::writeCSV(QString filename)
{

}
