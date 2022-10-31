#include <DApplication>
#include <DMainWindow>
#include <DWidgetUtil>
#include <DApplicationSettings>
#include <DTitlebar>
#include <DFontSizeManager>

#include "mainwindow.h"

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    DApplication a(argc, argv);
    a.setOrganizationName("deepin");
    a.setApplicationName("dtk-application");
    a.setApplicationVersion("1.0");
    a.setProductIcon(QIcon(":/images/logo.svg"));
    a.setProductName("Dtk Application");
    a.setApplicationDescription("This is a dtk template application.");

    a.loadTranslator();
    a.setApplicationDisplayName(QCoreApplication::translate("Main", "DTK Application"));

    // 保存程序的窗口主题设置
    DApplicationSettings as;
    Q_UNUSED(as)

    MainWindow w;
    // 设置标题，宽度不够会隐藏标题文字
//    w.setMinimumSize(QSize(600, 200));
//    w.titlebar()->setWindowFlag(Qt::Window | Qt::WindowContextHelpButtonHint | Qt::WindowMinimizeButtonHint)

    w.show();
    Dtk::Widget::moveToCenter(&w);

    return a.exec();
}
