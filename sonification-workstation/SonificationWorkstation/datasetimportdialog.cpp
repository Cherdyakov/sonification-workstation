#include "datasetimportdialog.h"
#include <QHeaderView>

namespace sow {

DatasetImportDialog::DatasetImportDialog(QString path)
{
    // Set dialog properties.
    this->setModal(true);
    this->setWindowTitle("Dataset Import Preview");

    // Create default dialog buttons and connect signals.
    buttonBox_ = new QDialogButtonBox(QDialogButtonBox::Ok |
                                      QDialogButtonBox::Cancel);
    connect(buttonBox_, &QDialogButtonBox::accepted,
            this, &DatasetImportDialog::onAccepted);
    connect(buttonBox_, &QDialogButtonBox::rejected,
            this, &DatasetImportDialog::onRejected);

    // Create orientation combobox and connect signals.
    orientationComboBox_ = new QComboBox(this);
    orientationComboBox_->addItem("Columns");
    orientationComboBox_->addItem("Rows");
    connect(orientationComboBox_, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &DatasetImportDialog::onOrientationChanged);

    // Label for orientation combobox.
    orientationLabel_ = new QLabel(this);
    orientationLabel_->setText("Data tracks are mapped from csv: ");


    // TableWidget setup.
    table_ = new QTableWidget(this);
    table_->setRowCount(10);
    table_->setColumnCount(10);
    table_->setHorizontalHeaderLabels(headers_);
    table_->setVerticalHeaderLabels(headers_);
    setColsTracks();

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
    // Child layouts.
    QHBoxLayout* orientationLayout = new QHBoxLayout(this);
    orientationLabel_->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    orientationLayout->addWidget(orientationLabel_);
    orientationLayout->addWidget(orientationComboBox_);
    orientationLayout->addStretch();

    // Add widgets to main layout.
    mainLayout->addLayout(orientationLayout);
    mainLayout->addWidget(table_);
    mainLayout->addWidget(buttonBox_);
    setLayout(mainLayout);
    this->adjustSize();
}

void DatasetImportDialog::setRowsTracks()
{
    table_->horizontalHeader()->hide();
    table_->verticalHeader()->show();
}

void DatasetImportDialog::setColsTracks()
{
    table_->verticalHeader()->hide();
    table_->horizontalHeader()->show();
}

void DatasetImportDialog::onAccepted()
{
    done(orientationComboBox_->currentIndex() + 1);
}

void DatasetImportDialog::onRejected()
{
    reject();
}

void DatasetImportDialog::onOrientationChanged(int idx)
{
    if(idx == 0) {
        setColsTracks();
    } else {
        setRowsTracks();
    }
}

}
