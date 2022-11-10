#include <QString>

#ifndef CONTAINER_H
#define CONTAINER_H


class Container
{
public:
    Container();
    Container(QString ContainerId,QString Name,QString State,QString Image,QString Port,QString Command);
    QString GetContainerId();
    QString SetContainerId();
    QString GetName();
    QString SetName();
    QString GetState();
    QString SetState();

private:
    QString ContainerId;  // 容器id
    QString Name;         // 容器名
    QString State;        // 容器运行状态
    QString Image;        // 使用的镜像
    QString Port;         // 暴露端口
    QString Command;      // 容器执行指令
};

#endif // CONTAINER_H
