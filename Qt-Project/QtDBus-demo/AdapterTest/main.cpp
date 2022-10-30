#include <QCoreApplication>
#include <QDBusConnection>
#include <QDebug>
#include <QDBusError>
#include "server.h"
#include "valueAdaptor.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QDBusConnection connection = QDBusConnection::sessionBus();
    server object(70);
    //ValueAdaptor是qdbusxml2cpp生成的Adaptor类
    ValueAdaptor valueAdaptor(&object);
    if (!connection.registerService("com.bluesky.test"))
    {
        qDebug() << connection.lastError().message();
        exit(1);
    }
    connection.registerObject("/test/objects", &object);
    return a.exec();
}
