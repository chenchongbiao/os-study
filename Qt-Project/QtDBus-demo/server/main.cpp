#include <QCoreApplication>
#include <QtDBus/QDBusConnection>
#include <QDebug>
#include <QtDBus/QDBusError>
#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //建立到session bus的连接
    QDBusConnection connection = QDBusConnection::sessionBus();
    //在session bus上注册名为com.bluesky.test的服务
    if(!connection.registerService("com.bluesky.test"))
    {
        qDebug() << "error:" << connection.lastError().message();
        exit(-1);
    }
    server object(60);
    //注册名为/test/objects的对象，把类Object所有槽函数导出为object的method
    connection.registerObject("/test/objects", &object,QDBusConnection::ExportAllSlots);

    return a.exec();
}
