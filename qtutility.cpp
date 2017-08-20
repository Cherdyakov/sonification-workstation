#include "qtutility.h"

QList<int> vecToQList(std::vector<int> vec)
{
    QList<int> list;
    for(unsigned int i = 0; i < vec.size(); i++)
    {
        list.push_back(vec[i]);
    }
    return list;
}

QList<double> vecToQList(std::vector<double> vec)
{
    QList<double> list;
    for(unsigned int i = 0; i < vec.size(); i++)
    {
        list.push_back(vec[i]);
    }
    return list;
}

QList<QString> vecToQList(std::vector<std::__cxx11::string> vec)
{
    QList<QString> list;
    for(unsigned int i = 0; i < vec.size(); i++)
    {
        QString s = QString::fromStdString(vec[i]);
        list.push_back(s);
    }
    return list;
}
