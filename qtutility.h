#ifndef QTUTILITY_H
#define QTUTILITY_H

#include <QList>
#include <QVariant>

#include <vector>

QList<int> vecToQList(std::vector<int> vec);
QList<double> vecToQList(std::vector<double> vec);
QList<QString> vecToQList(std::vector<std::string> vec);

#endif // QTUTILITY_H
