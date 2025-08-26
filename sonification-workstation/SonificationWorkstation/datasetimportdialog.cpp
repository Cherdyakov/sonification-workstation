 #include "datasetimportdialog.h"
#include <QHeaderView>

namespace sow {

DatasetImportDialog::DatasetImportDialog(QString path)
{
    // Set dialog properties.
    this->setModal(true);
    this->setWindowTitle("Dataset Import Preview");
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    // Create default dialog buttons and connect signals.
    buttonBox_ = new QDialogButtonBox(QDialogButtonBox::Ok |
                                      QDialogButtonBox::Cancel);
    connect(buttonBox_, &QDialogButtonBox::accepted,
            this, &DatasetImportDialog::onAccepted);
    connect(buttonBox_, &QDialogButtonBox::rejected,
            this, &DatasetImportDialog::onRejected);

    // Create orientation combobox and connect signals.
    orientationComboBox_ = new QComboBox(this);
    orientationComboBox_->setObjectName("OrientationComboBox");
    orientationComboBox_->setAccessibleName("Orientation dropdown, selects whether Sonification Workstation tracks are mapped from data columns or data rows.");
    orientationComboBox_->setAccessibleDescription("");
    orientationComboBox_->addItem("Columns");
    orientationComboBox_->addItem("Rows");
    connect(orientationComboBox_, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &DatasetImportDialog::onOrientationChanged);

    // Create header combobox and connect signals.
//    headerComboBox_ = new QComboBox(this);
//    headerComboBox_->addItem("Load as Headers");
//    headerComboBox_->addItem("Load as Data");
//    connect(headerComboBox_, QOverload<int>::of(&QComboBox::currentIndexChanged),
//            this, &DatasetImportDialog::onHeaderComboBoxChanged);

    // Label for orientation combobox.
    orientationLabel_ = new QLabel(this);
    orientationLabel_->setText("Tracks mapped from: ");
    // Labels for header comboboxes.
//    headerLabel_ = new QLabel(this);
//    headerLabel_->setText("Header values: ");

    // TableWidget setup.
    table_ = new QTableWidget(this);
    table_->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table_->setRowCount(10);
    table_->setColumnCount(10);
    table_->setHorizontalHeaderLabels(headers_);
    table_->setVerticalHeaderLabels(headers_);
    // Tab goes to next widget, use arrow keys to navigate inside the table.
    // Otherwise screen-reader users can't easily navigate out of table.
    table_->setTabKeyNavigation(false);
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
    QVBoxLayout* mainLayout = new QVBoxLayout;
    table_->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    // Child layouts.
    QHBoxLayout* settingsLayout = new QHBoxLayout;
    orientationLabel_->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    settingsLayout->addWidget(orientationLabel_);
    settingsLayout->addWidget(orientationComboBox_);
    settingsLayout->addStretch();

    // Add widgets to main layout.
    mainLayout->addLayout(settingsLayout);
    mainLayout->addWidget(table_);
    mainLayout->addWidget(buttonBox_);
    setLayout(mainLayout);
    this->adjustSize();
}

void DatasetImportDialog::setRowsTracks()
{
    useColumns_ = false;
    table_->horizontalHeader()->hide();
    table_->verticalHeader()->show();
}

void DatasetImportDialog::setColsTracks()
{
    useColumns_ = true;
    table_->verticalHeader()->hide();
    table_->horizontalHeader()->show();
}

void DatasetImportDialog::onAccepted()
{
    int returnCode = 1;

    if (useColumns_) {
        returnCode = returnCode | constants::COLUMNS_FLAG;
    }

//    if (useHeaders_) {
//        returnCode = returnCode | constants::HEADERS_FLAG;
//    }

    qDebug() << returnCode;
    done(returnCode);
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

//void DatasetImportDialog::onHeaderComboBoxChanged(int idx)
//{
//    useHeaders_ = static_cast<bool>(idx);
//}

} // namespace sow
