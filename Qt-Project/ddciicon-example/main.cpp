#include <DApplication>
#include <DWidgetUtil>
#include <DMainWindow>
#include <DIconButton>

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    DApplication a(argc, argv);
    
    DMainWindow w;
    w.show();

    Dtk::Widget::moveToCenter(&w);
    return a.exec();
}