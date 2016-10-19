#include "tablemodel.h"

TableModel::TableModel()
{

}

int TableModel::rowCount(const QModelIndex &parent) const
{
    qDebug() << "rowCount";
    return 1;//m_data.count() / width;
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    qDebug() << "colCount";
    return 2;//width;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    qDebug() << "data";
    if (role == Qt::DisplayRole)
    {
        return QString("Some data");
    }
    return QVariant();
}

//QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
//{

//}


