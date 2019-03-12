#include "qtutility.h"

QList<int> vecToQList(QVector<int> vec)
{
    QList<int> list;
    for(unsigned int i = 0; i < vec.size(); i++)
    {
        list.push_back(vec[i]);
    }
    return list;
}

QList<double> vecToQList(QVector<double> vec)
{
    QList<double> list;
    for(unsigned int i = 0; i < vec.size(); i++)
    {
        list.push_back(vec[i]);
    }
    return list;
}

QList<QString> vecToQList(QVector<std::__cxx11::string> vec)
{
    QList<QString> list;
    for(unsigned int i = 0; i < vec.size(); i++)
    {
        QString s = QString::fromStdString(vec[i]);
        list.push_back(s);
    }
    return list;
}
