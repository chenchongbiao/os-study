#include <DConfig>
#include <QDir>
#include <QDebug>

#include "helper.hpp"

#define PREFIX "/usr"

DCORE_USE_NAMESPACE

static constexpr char const *APP_ID = "tests";
static constexpr char const *FILE_NAME = "example";

static EnvGuard fileBackendLocalPerfix;
static EnvGuard backendType;
static FileCopyGuard *metaGuard = nullptr;

int main(int argc, char *argv[])
{
    fileBackendLocalPerfix.set("DSG_DCONFIG_FILE_BACKEND_LOCAL_PREFIX", "/tmp/example");
    
    // 将data/dconf-example.meta.json拷贝到/tmp/example/usr/share/dsg/configs/tests/example.json
    metaGuard = new FileCopyGuard(":/data/dconf-example.meta.json", \
                    QString("%1" PREFIX"/share/dsg/configs/%2/%3.json") \
                    .arg(fileBackendLocalPerfix.value(), APP_ID, FILE_NAME));
    // 设置后端类型为FileBackend
    backendType.set("DSG_DCONFIG_BACKEND_TYPE", "FileBackend");
    // 设置APP_ID为tests
    backendType.set("DSG_APP_ID", APP_ID);
    {
        qDebug() << "------------------------------------------------------------";
        // 构造配置策略提供的对象,指定配置所属的应用"tests",文件名"example"
        QScopedPointer<DConfig> config(DConfig::create(APP_ID, FILE_NAME));

        // 返回配置策略后端名称 "FileBackend"
        qDebug() << QString("配置策略后端名称：%1").arg(config->backendName());

        // 判断此后端是否可用，可用为true，否则为false
        qDebug() << QString("判断后端是否可用：") << config->isValid();
    }
    {
        qDebug() << "------------------------------------------------------------";
        // 构造配置策略提供的对象,指定配置所属的应用"tests",文件名"example"
        QScopedPointer<DConfig> config(DConfig::create(APP_ID, FILE_NAME));

        // 根据配置项名称获得对应值 true 类型为Bool
        qDebug() << QString("配置项目canExit对应的值：") << config->value("canExit").toBool();

        // 根据配置项名称获得对应值 "126" 类型为String
        qDebug() << QString("配置项目key2对应的值：") << config->value("key2").toString();

        // 根据配置项名称获得对应值 ["value1", "value2"] 类型为StringList
        qDebug() << QString("配置项目array对应的值：") << config->value("array").toStringList();

        // 根据配置项名称获得对应值 {"key1": "value1", "key2": "value2"} 类型为map
        qDebug() << QString("配置项目map对应的值：") << config->value("map").toMap();
    }
    {
        qDebug() << "------------------------------------------------------------";
        // 构造配置策略提供的对象,指定配置所属的应用"tests",文件名"example"
        QScopedPointer<DConfig> config(DConfig::create(APP_ID, FILE_NAME));

        // 根据配置项名称设置其值，设置canExit对应值为 true 类型为String
        config->setValue("canExit", false);
        // 再次打印canExit的值，此时为 false
        qDebug() << QString("设置canExit对应的值为：") << config->value("canExit").toBool();

        // 根据配置项名称设置其值，设置key2对应值为"125" 类型为String
        config->setValue("key2", "125");
        // 再次打印key2的值，此时为"125"
        qDebug() << QString("设置key2对应的值为：") << config->value("key2").toString();

        const QStringList array{"1", "2"};
        // 根据配置项名称设置其值，设置array对应值为["1", "2"] 类型为StringList
        config->setValue("array", array);
        // 再次打印array的值，此时为["1", "2"]
        qDebug() << QString("设置array对应的值为：") << config->value("array").toStringList();

        QVariantMap map;
        map.insert("key1", "update1");
        map.insert("key2", "update2");
        // 根据配置项名称设置其值，设置array对应值为{"key1": "update1", "key2": "update2"} 类型为map
        config->setValue("map", map);
        // 再次打印array的值，此时为{"key1": "update1", "key2": "update2"}
        qDebug() << QString("设置map对应的值为：") << config->value("map").toMap();
    }
    {
        qDebug() << "------------------------------------------------------------";
        // 构造配置策略提供的对象,指定配置所属的应用"tests",文件名"example"
        QScopedPointer<DConfig> config(DConfig::create(APP_ID, FILE_NAME));

        // reset() 设置其配置项对应的默认值,此值为经过override机制覆盖后的值,不一定为此配置文件中meta中定义的值 

        config->reset("canExit");
        // 再次打印canExit的值，此时为 true
        qDebug() << QString("重置canExit对应的值为：") << config->value("canExit").toBool();

        config->reset("key2");
        // 再次打印key2的值，此时为 "126"
        qDebug() << QString("重置key2对应的值为：") << config->value("key2").toString();

        config->reset("array");
        // 再次打印array的值，此时为["value1", "value2"],
        qDebug() << QString("重置array对应的值为：") << config->value("array").toStringList();

        config->reset("map");
        // 再次打印array的值，此时为{"key1": "value1", "key2": "value2"}
        qDebug() << QString("重置map对应的值为：") << config->value("map").toMap();
    }
    {
        qDebug() << "------------------------------------------------------------";
        // 构造配置策略提供的对象,指定配置所属的应用"tests",文件名"example"
        QScopedPointer<DConfig> config(DConfig::create(APP_ID, FILE_NAME));
        QStringList keyList{QString("key1"), QString("key2"), QString("canExit")};
        qDebug() << QString("配置项名称集合") << config->keyList();
    }

    QDir(fileBackendLocalPerfix.value()).removeRecursively();
    // 重置环境变量
    fileBackendLocalPerfix.restore();
    backendType.restore();
    delete metaGuard;

    return 0;
}
