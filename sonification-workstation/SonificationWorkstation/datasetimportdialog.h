#ifndef DATASETIMPORTDIALOG_H
#define DATASETIMPORTDIALOG_H

#include <QDialog>
#include <QLayout>
#include <QComboBox>
#include <QLabel>
#include <QDialogButtonBox>
#include <QTableWidget>
#include "constants.h"
#include "filereader.h"

namespace sow {

class DatasetImportDialog : public QDialog
{
public:
    DatasetImportDialog(QString path);

private:

    QStringList headers_ = { "A", "B", "C", "D", "E",
                             "F", "G", "H", "I", "J" };

    bool useColumns_ = true;
//    bool useHeaders_ = true;

    QDialogButtonBox* buttonBox_;
    QLabel* orientationLabel_;
//    QLabel* headerLabel_;
//    QLabel* rowHeaderLabel_;
//    QComboBox* headerComboBox_;
    QComboBox* orientationComboBox_;
    QTableWidget* table_;

    void setRowsTracks();
    void setColsTracks();

signals:


private slots:

    void onAccepted();
    void onRejected();
    void onOrientationChanged(int idx);
//    void onHeaderComboBoxChanged(int idx);

};

} // namespace sow

#endif // DATASETIMPORTDIALOG_H
