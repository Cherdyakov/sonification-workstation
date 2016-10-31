#include "horizontalproxymodel.h"
#include <qdebug.h>

HorizontalProxyModel::HorizontalProxyModel(QObject *parent) : QAbstractProxyModel(parent)
{
}

QModelIndex HorizontalProxyModel::mapToSource(const QModelIndex &proxyIndex) const
{
    if (!sourceModel())
    {
        return QModelIndex();
    }
    return sourceModel()->index(proxyIndex.column(), proxyIndex.row());
}

QModelIndex HorizontalProxyModel::mapFromSource(const QModelIndex &sourceIndex) const
{
    if(!sourceModel())
    {
        return QModelIndex();
    }
    return index(sourceIndex.column(), sourceIndex.row());
}

QModelIndex HorizontalProxyModel::index(int row, int column, const QModelIndex &) const
{
    return createIndex(row, column, (void*) 0);
}

QModelIndex HorizontalProxyModel::parent(const QModelIndex &) const
{
    return QModelIndex();
}

int HorizontalProxyModel::rowCount(const QModelIndex &) const
{
    qDebug() << "proxy rowCount";
    if(!sourceModel())
    {
        return 0;
    }
    return sourceModel()->columnCount();
}

int HorizontalProxyModel::columnCount(const QModelIndex &) const
{
    qDebug() << "proxy colCount";
    if(!sourceModel())
    {
        return 0;
    }
    return sourceModel()->rowCount();
}

QVariant HorizontalProxyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (!sourceModel())
    {
        return 0;
    }
    Qt::Orientation new_orientation = orientation == Qt::Horizontal ? Qt::Vertical : Qt::Horizontal;
    return sourceModel()->headerData(section, new_orientation, role);
}

QVariant HorizontalProxyModel::data(const QModelIndex &proxyIndex, int role) const
{
    if(role != Qt::DisplayRole)
    {
        return QVariant();
    }
    return sourceModel()->data(sourceModel()->index(proxyIndex.column(), proxyIndex.row()));
}


