#include "tablemodel.h"

TableModel::TableModel(QObject *parent) :
    QAbstractTableModel(parent)
{

}

int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_data.count();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    if(m_data.count() < 1)
    {
        return 0;
    }
    return m_data[0].count();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        if (section % 2 == 0)
            return "x";
        else
            return "y";
    } else {
        return QString("%1").arg(section + 1);
    }
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
//    qDebug() << "index: " << index.row() << "," << index.column();
    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }
    return m_data[index.row()].at(index.column());
}

//bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
//{
//    if (index.isValid() && role == Qt::EditRole) {
//        m_data[index.row()].replace(index.column(), value.toDouble());
//        emit dataChanged(index, index);
//        return true;
//    }
//    return false;
//}

void TableModel::appendRow(QVector<double> row)
{
    emit layoutAboutToBeChanged();
    emit beginInsertRows(QModelIndex(), rowCount(), rowCount());

    m_data.append(row);

    emit endInsertRows();
    emit layoutChanged();
}

void TableModel::clear()
{
    for(int i = 0; i < m_data.count(); ++i)
    {
        m_data[i].clear();
    }
    m_data.clear();
}

//QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
//{

//}


