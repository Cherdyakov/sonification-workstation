#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QDebug>
#include <QStandardItem>

class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    TableModel();
    Q_INVOKABLE virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    Q_INVOKABLE virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    Q_INVOKABLE virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
//    Q_INVOKABLE virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;


    void setDataVector(QVector<double> *data);
    void appendRow(QVector<double> row);
    int getWidth() const;
    void setWidth(int value);

private:

    int width;
    QVector<double>* m_data;


};

#endif // TABLEMODEL_H

