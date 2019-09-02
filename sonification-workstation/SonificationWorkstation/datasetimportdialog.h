#ifndef DATASETIMPORTDIALOG_H
#define DATASETIMPORTDIALOG_H

#include <QDialog>
#include <QLayout>
#include <QDialogButtonBox>
#include <QTableWidget>
#include "filereader.h"

namespace sow {

class DatasetImportDialog : public QDialog
{
public:
    DatasetImportDialog(QString path);

private:
    QDialogButtonBox* buttonBox_;
    QTableWidget* table_;

};

}

#endif // DATASETIMPORTDIALOG_H
