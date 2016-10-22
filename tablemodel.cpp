#include "tablemodel.h"

TableModel::TableModel()
{
    width = 0;
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    int count;
    if(width == 0)
    {
        count = 0;
    }
    else
    {
        count = m_data->count() / width;
    }
    qDebug() << "tablemodel rowCount: " << count;
    return count;
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    qDebug() << "tablemodel: colCount " << width;
    return width;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    qDebug() << "tablemodel: data";
    if (role == Qt::DisplayRole)
    {
        int idx = index.row() * width + index.column();
        return (*m_data)[idx];
    }
    return QVariant();
}

void TableModel::setDataVector(QVector<double> *data)
{
    m_data = data;
}

void TableModel::appendRow(QVector<double> row)
{
    if(!m_data)
    {
        qDebug() << "invalid m_data";
        return;
    }

    emit layoutAboutToBeChanged();
    emit beginInsertRows(QModelIndex(), rowCount(), rowCount());
    for(int i = 0; i < row.count(); ++i)
    {
        m_data->push_back(row[i]);
    }
    width = row.count();
    emit endInsertRows();
    emit layoutChanged();

    qDebug() << (*m_data);

}

void TableModel::clear()
{
    m_data->clear();
}

int TableModel::getWidth() const
{
    return width;
}

void TableModel::setWidth(int value)
{
    width = value;
}

//QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
//{

//}


