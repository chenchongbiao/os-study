#include <DConfigFile>
#include <QDebug>
#include <QCoreApplication>
#include <unistd.h>

DCORE_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // 构造DConfigFile，元数据文件名example，与元数据安装目录的/usr/share/dsg/configs/APPID名(可执行文件名)对应目录/example.json，
    DConfigFile configFile("dconfigfile-example","example");
    // 解析配置文件 
    configFile.load();

    // 创建用户缓存
    QScopedPointer<DConfigCache> userCache(configFile.createUserCache(getuid()));
    // 解析配置文件
    userCache->load();

    // 判断是否有效
    if (!configFile.isValid()) {
        qWarning() << QString("DConfig无效.");
        return 0;
    }

    // meta 返回原型对象, keyList获取所有配置项的key
    qDebug() << "所有的所有配置项的key:" << configFile.meta()->keyList();

    // 获取指定配置项的值，配置项可以是字符串，数组，map容器，布尔值，整型，详见example.json
    qDebug() << "canExit对应的值:" <<  configFile.value("canExit").toBool();
    
    // 配置项的可见性，其余配置项标记、配置项的权限可查看文档
    qDebug() << "配置项的可见性" << configFile.meta()->visibility("canExit");

    QVariantMap map;
    map.insert("k1","v1");
    map.insert("k2","v2");
    // 设置map的值
    configFile.setValue("map", map, "dconfigfile-example", userCache.get());

    configFile.save();

    // root用户运行，save的数据会保存到/root/.config/dsg/configs-fake-global/dconfigfile-example/example.json
    // map数据对应的flags标记为NoOverride，配置项允许被覆盖，如果flags为global泽忽略用户身份，详见文档。
    userCache->save();
    qDebug() << configFile.cacheValue(userCache.get(), "map");

    return a.exec();
}
