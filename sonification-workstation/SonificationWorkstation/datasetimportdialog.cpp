#include "datasetimportdialog.h"

namespace sow {

DatasetImportDialog::DatasetImportDialog(QString path)
{
    // Set dialog properties.
    setModal(true);

    // Create buttons and set button roles.
    buttonBox_ = new QDialogButtonBox(QDialogButtonBox::Ok |
                                      QDialogButtonBox::Cancel);

    // Get the CSV preview data and add to QTableWidget for preview.
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

    // Layout for dialog box.
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Add widgets
    mainLayout->addWidget(table_);
    mainLayout->addWidget(buttonBox_);
    setLayout(mainLayout);
}

}
