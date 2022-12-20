#include <DConfig>
#include <QDebug>
#include <QCoreApplication>

DCORE_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    // 构造DConfig，元数据文件名example，与元数据安装目录的/usr/share/dsg/configs/APPID名(可执行文件名)对应目录/example.json，
    DConfig config("example");

    // 判断是否有效
    if (!config.isValid()) {
        qWarning() << QString("DConfig无效, name:[%1].").
                      arg(config.name());
        return 0;
    }

    // 获取所有配置项的key
    qDebug() << "所有的所有配置项的key:" << config.keyList();

    // 获取指定配置项的值，配置项可以是字符串，数组，map容器，布尔值，整型，详见example.json
    qDebug() << "canExit对应的值:" << config.value("canExit").toBool();

    QVariantMap map;
    for (int i = 0; i < 1; i++) {
        QVariantMap nestItem;
        for (int j = 0; j < 1; j++) {
            nestItem[QString::number(j)] = QString::number(j);
        }
        map[QString::number(i)] = nestItem;
    }

    QScopedPointer<DConfig> heapConfig;
    heapConfig.reset(new DConfig("example"));

    if (!heapConfig->isValid()) {
        qWarning() << QString("DConfig无效, name:[%1].").
                      arg(heapConfig->name());
        return 0;
    }

    // 监听值改变的信号
    const bool &oldValue = heapConfig->value("canExit").toBool();
    QObject::connect(heapConfig.get(), &DConfig::valueChanged, [oldValue,&heapConfig](const QString &key){
        qDebug() << "canExit原来的值:" << oldValue << ", canExit新的值:" << heapConfig->value(key).toBool();
    });

    // 重置canExit的值
    heapConfig->setValue("canExit", !oldValue);

    return a.exec();
}