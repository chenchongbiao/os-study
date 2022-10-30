#include <QCoreApplication>
#include <QtDBus/QDBusMessage>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusReply>
#include <QtDBus/QDBusInterface>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    // 创建QDBusInterface接口，服务名称为：com.bluesky.test，对象路径为：/test/objects
    // 接口名称为com.bluesky.test.value
    QDBusInterface interface("com.bluesky.test", "/test/objects",
                             "com.bluesky.test.value",
                             QDBusConnection::sessionBus());
    if (!interface.isValid())
    {
        qDebug() << qPrintable(QDBusConnection::sessionBus().lastError().message());
        exit(1);
    }
    //调用远程的value方法
    QDBusReply<int> reply = interface.call("value");
    if (reply.isValid())
    {
        int value = reply.value();
        qDebug() << QString("value =  %1").arg(value);
    }
    else
    {
        qDebug() << "value method called failed!";
    }

    return a.exec();
}
