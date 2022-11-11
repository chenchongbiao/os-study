#include <QSqlQuery>

#include "model/container.h"
#include "containermapper.h"

ContainerMapper::ContainerMapper()
{

}

bool ContainerMapper::Insert(Container container)
{
    QSqlQuery query;
    bool result = query.exec(QString(R"(INSERT INTO container (container_id,name,image,state,port,command) values(%1,%2,%3,%4,%5,%6);)")
               .arg(container.GetContainerId())
               .arg(container.GetName())
               .arg(container.GetImage())
               .arg(container.GetState())
               .arg(container.GetPort())
               .arg((container.GetCommand())));
    return result;
}

QSqlQuery ContainerMapper::GetContainerList()
{
    QSqlQuery query;
    query.exec(QString(R"(SELECT container_id,name,state,image,port FROM container;)"));
    return query;
}
