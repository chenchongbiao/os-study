#include <DApplication>
#include <DWidgetUtil>
#include <DIconButton>
#include <DDciIcon>
#include <QFile>
#include <QtDebug>
#include <QPixmap>
#include <QLineEdit>
#include <QFormLayout>
#include <DIconButton>
#include <QWidget>
#include <QLabel>

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    DApplication a(argc, argv);
    
    QWidget w;  // 初始化主窗口
    QFormLayout* layout = new QFormLayout(&w);

    QFile file(":/dsg/built-in-icons/select_indicator.dci");
    file.open(QIODevice::ReadOnly);
    DDciIcon dci(file.fileName());

    auto icon = dci.matchIcon(0, DDciIcon::Light, DDciIcon::Hover);
    qDebug() << "DCI图标的实际大小" << dci.actualSize(icon);

    layout->addRow("icon button", new DIconButton(dci));

    QLabel *label = new QLabel();
    label->setPixmap(dci.pixmap(1.0, 0, icon));
    layout->addRow("icon", label);


    w.show();
    Dtk::Widget::moveToCenter(&w);
    return a.exec();
}
