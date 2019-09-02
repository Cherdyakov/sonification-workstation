#ifndef DATASETIMPORTDIALOG_H
#define DATASETIMPORTDIALOG_H

#include <QDialog>
#include <QLayout>
#include <QComboBox>
#include <QLabel>
#include <QDialogButtonBox>
#include <QTableWidget>
#include "filereader.h"

namespace sow {

class DatasetImportDialog : public QDialog
{
public:
    DatasetImportDialog(QString path);

private:

    QStringList headers_ = { "A", "B", "C", "D", "E",
                             "F", "G", "H", "I", "J" };

    QDialogButtonBox* buttonBox_;
    QLabel* orientationLabel_;
    QComboBox* orientationComboBox_;
    QTableWidget* table_;

    void setRowsTracks();
    void setColsTracks();

signals:

//    void newDataset(const QString path);

private slots:

    void onAccepted();
    void onRejected();
    void onOrientationChanged(int idx);

};

}

#endif // DATASETIMPORTDIALOG_H
