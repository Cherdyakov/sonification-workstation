#ifndef HORIZONTALPROXYMODEL_H
#define HORIZONTALPROXYMODEL_H

#include <QAbstractProxyModel>
#include <QModelIndex>

class HorizontalProxyModel : public QAbstractProxyModel
{

public:
  HorizontalProxyModel(QObject * parent = 0);
  QModelIndex mapToSource(const QModelIndex &proxyIndex) const Q_DECL_OVERRIDE;
  QModelIndex mapFromSource(const QModelIndex &sourceIndex) const Q_DECL_OVERRIDE;
  QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
  QModelIndex parent(const QModelIndex &child) const Q_DECL_OVERRIDE;
  int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
  int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
  QVariant data(const QModelIndex &proxyIndex, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
//  bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
};

#endif // HORIZONTALPROXYMODEL_H
