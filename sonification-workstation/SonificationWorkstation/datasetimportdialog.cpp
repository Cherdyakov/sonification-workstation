#include "datasetimportdialog.h"

namespace sow {

DatasetImportDialog::DatasetImportDialog(QString path)
{
    // Set dialog properties.
    setModal(true);

    // Get the CSV preview data and add to QTableWidget.
    FileReader reader;
    QList<QStringList> dataPreview = reader.previewCSV(path);

    table_ = new QTableWidget(this);
    table_->setRowCount(dataPreview.count());
    table_->setColumnCount(dataPreview[0].count());

    for(int i = 0; i < dataPreview.count(); i++)
    {
        for(int j = 0; j < dataPreview[0].count(); j++) {
            QTableWidgetItem* item = new QTableWidgetItem(dataPreview[i][j]);
            table_->setItem(i, j, item);
        }
    }

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(table_);
    setLayout(mainLayout);
}

}
