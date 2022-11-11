#include <QSqlQuery>

#include "model/container.h"

#ifndef CONTAINERMAPPER_H
#define CONTAINERMAPPER_H


class ContainerMapper
{
public:
    ContainerMapper();
    bool Insert(Container container);  // 插入数据
    QSqlQuery GetContainerList();  // 获取容器列表数据
};

#endif // CONTAINERMAPPER_H
