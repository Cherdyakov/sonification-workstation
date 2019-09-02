#include "datasetimportdialog.h"

namespace sow {

DatasetImportDialog::DatasetImportDialog(QString path)
{
    // Set dialog properties.
    setModal(true);

    // Create buttons and connect signals.
    buttonBox_ = new QDialogButtonBox(QDialogButtonBox::Ok |
                                      QDialogButtonBox::Cancel);
    connect(buttonBox_, &QDialogButtonBox::accepted,
            this, &DatasetImportDialog::onAccepted);
    connect(buttonBox_, &QDialogButtonBox::rejected,
            this, &DatasetImportDialog::onRejected);

    // TableWidget setup.
    table_ = new QTableWidget(this);
    table_->setRowCount(10);
    table_->setColumnCount(10);
    table_->setHorizontalHeaderLabels({ "A", "B", "C", "D", "E",
                                        "F", "G", "H", "I", "J" });

    // Get the CSV preview data and add to QTableWidget for preview.
    FileReader reader;
    QList<QStringList> dataPreview = reader.previewCSV(path);
    for(int i = 0; i < dataPreview.count(); i++)
    {
        for(int j = 0; j < dataPreview[0].count(); j++) {
            QTableWidgetItem* item = new QTableWidgetItem(dataPreview[i][j]);
            table_->setItem(i, j, item);
        }
    }

    // Main layout for this dialog box.
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    table_->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

    // Add widgets to main layout.
    mainLayout->addWidget(table_);
    mainLayout->addWidget(buttonBox_);
    setLayout(mainLayout);
    this->adjustSize();
}

void DatasetImportDialog::onAccepted()
{
    accept();
}

void DatasetImportDialog::onRejected()
{
    reject();
}

}
