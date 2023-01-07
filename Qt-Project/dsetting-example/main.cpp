#include <QCoreApplication>
#include <DSettings>
#include <qsettingbackend.h>
#include <DSettingsGroup>
#include <DSettingsOption>
#include <QTemporaryFile>
#include <QDebug>

DCORE_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // 初始化一个存储后端
    QTemporaryFile tmpFile;
    tmpFile.open();
    QPointer<QSettingBackend> backend = new QSettingBackend(tmpFile.fileName());

    // 从json中初始化配置
    QPointer<DSettings> settings = DSettings::fromJsonFile(":/data/settings.json");
    settings->setBackend(backend);

    // 读取配置
    // 该组中包含一个base的root组,两个子组: open_action/new_tab_windows,每个子组有包含若干选项。
    // 对于"New Window Open:"这个配置,其完整的访问id为base.new_tab_windows.new_window_path。
    QPointer<DSettingsOption> opt = settings->option("base.new_tab_windows.new_window_path");
    qDebug() << opt->value();

    // 修改配置
    opt->setValue("Test");
    qDebug() << opt->value();

    // 获取所有keys
    QStringList keys = settings->keys();
    qDebug() << keys;

    // base.open_action对应的组
    QPointer<DSettingsGroup> group = settings->group("base.open_action");
    qDebug() << group->key();

    return a.exec();
}
