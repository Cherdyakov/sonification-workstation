#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QDebug>
#include <QStandardItem>

class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    TableModel(QObject *parent);
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
//    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    void appendRow(QVector<double> row);
//    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
//    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
//    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
//    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex());
//    bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex());

    void clear();


private:

    QList<QVector<double>> m_data;


};

#endif // TABLEMODEL_H

