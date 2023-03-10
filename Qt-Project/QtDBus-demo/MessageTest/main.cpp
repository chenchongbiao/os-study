#include <QCoreApplication>
#include <QtDBus/QDBusMessage>
#include <QtDBus/QDBusConnection>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //构造一个method_call消息，服务名称为：com.bluesky.test，对象路径为：/test/objects
    //接口名称为com.bluesky.test.value，method名称为value
    QDBusMessage message = QDBusMessage::createMethodCall("com.bluesky.test",
                           "/test/objects",
                           "com.bluesky.test.value",
                           "value");
    //发送消息
    QDBusMessage response = QDBusConnection::sessionBus().call(message);
    //判断method是否被正确返回
    if (response.type() == QDBusMessage::ReplyMessage)
    {
        //从返回参数获取返回值
        int value = response.arguments().takeFirst().toInt();
        qDebug() << QString("value =  %1").arg(value);
    }
    else
    {
        qDebug() << "value method called failed!";
    }

    return a.exec();
}
