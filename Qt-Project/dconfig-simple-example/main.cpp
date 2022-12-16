#include <DConfig>
#include <QDebug>
#include <csignal>
#include <QCoreApplication>

DCORE_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    // const QString appId = "dconfig-example";
    const QString fileName = "example";

    // 构造DConfig
    DConfig config(fileName);
    // QScopedPointer<DConfig> config(DConfig::create(appId, fileName));
    // 判断是否有效
    // if (!config.isValid()) {
    //     qWarning() << QString("DConfig无效, name:[%1], subpath[%2].").
    //                   arg(config.name(), config.subpath());
    //     return 0;
    // }
    
    // 异常处理，调用QCoreApplication::exit，使DConfig正常析构。
    std::signal(SIGINT, &QCoreApplication::exit);
    std::signal(SIGABRT, &QCoreApplication::exit);
    std::signal(SIGTERM, &QCoreApplication::exit);
    std::signal(SIGKILL, &QCoreApplication::exit) ;
    return a.exec();
}