#include <DConfig>
#include <QDebug>
#include <csignal>
#include <QCoreApplication>

DCORE_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    const QString fileName = "example";
    {
        // 构造DConfig
        DConfig config(fileName);

        // 判断是否有效
        if (!config.isValid()) {
            qWarning() << QString("DConfig无效, name:[%1], subpath[%2].").
                        arg(config.name(), config.subpath());
            return 0;
        }

        // 获取所有配置项的key
        qDebug() << "所有的所有配置项的key:" << config.keyList();

        // 返回配置策略后端名称 "DBusBackend"
        qDebug() << "配置策略后端名称:" << config.backendName();

        // 获取指定配置项的值
        qDebug() << "canExit对应的值:" << config.value("canExit").toBool();
    }
    {
        // 构造DConfig，subpath="/a"
        DConfig config(fileName,"/a");

        // 判断是否有效
        if (!config.isValid()) {
            qWarning() << QString("DConfig无效, name:[%1], subpath[%2].").
                        arg(config.name(), config.subpath());
            return 0;
        }

        // 获取指定配置项的值
        qDebug() << "subpath下key3对应的值:" << config.value("key3").toString();
    }
    {
        QVariantMap map;
        for (int i = 0; i < 1; i++) {
            QVariantMap nestItem;
            for (int j = 0; j < 1; j++) {
                nestItem[QString::number(j)] = QString::number(j);
            }
            map[QString::number(i)] = nestItem;
        }
        // 构造DConfig
        DConfig config(fileName);

        // 先打印一遍原来的值
        qDebug() <<  "第一次打印map对应的值:" << config.value("map", map);

        // 设置map对应的值为
        config.setValue("map", map);

        // 获取指定map对应的值
        qDebug() <<  "第二次打印map对应的值:" << config.value("map", map);

        // 重置map的值
        config.reset("map");
        // 获取指定map对应的值
        qDebug() <<  "第三次打印map对应的值:" << config.value("map", map);
        
    }
    // 异常处理，调用QCoreApplication::exit，使DConfig正常析构。
    std::signal(SIGINT, &QCoreApplication::exit);
    std::signal(SIGABRT, &QCoreApplication::exit);
    std::signal(SIGTERM, &QCoreApplication::exit);
    std::signal(SIGKILL, &QCoreApplication::exit) ;
    return a.exec();
}