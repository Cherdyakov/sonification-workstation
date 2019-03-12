#ifndef QTUTILITY_H
#define QTUTILITY_H

#include <QList>
#include <QVariant>

#include <vector>

QList<int> vecToQList(QVector<int> vec);
QList<double> vecToQList(QVector<double> vec);
QList<QString> vecToQList(QVector<std::string> vec);

#endif // QTUTILITY_H
