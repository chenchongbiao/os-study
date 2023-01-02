#include <DApplication>
#include <DWidgetUtil>
#include <DIconButton>
#include <DDciIcon>
#include <QFile>
#include <QtDebug>
#include <QFormLayout>
#include <DMainWindow>
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPalette>

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    DApplication a(argc, argv);
    DMainWindow win;

    QWidget w;
    QFormLayout* layout = new QFormLayout(&w);

    QFile file(":/dsg/built-in-icons/select_indicator.dci");
    file.open(QIODevice::ReadOnly);
    DDciIcon dci(file.fileName());

    auto icon = dci.matchIcon(0, DDciIcon::Light, DDciIcon::Hover);
    qDebug() << "DCI图标的实际大小" << dci.actualSize(icon);

    // 定义一个函数，传入DIconButton，以及提示信息
    auto addBtnRow = [&](DIconButton *iconBtn, const QString name){
        iconBtn->setIconSize(QSize(32,32));
        QHBoxLayout *hlayout = new QHBoxLayout();
        hlayout->addWidget(iconBtn);
        QLabel *btnLabel = new QLabel(name);
        hlayout->addWidget(btnLabel);
        return hlayout;
    };

    // 将DDciIcon传入DIconButton
    DIconButton *iconBtn1 = new DIconButton(dci);
    layout->addRow(addBtnRow(iconBtn1, "icon button"));

    DIconButton *iconBtn2 = new DIconButton(dci);
    iconBtn2->setDisabled(true);
    layout->addRow(addBtnRow(iconBtn2, "disabled state"));

    DIconButton *iconBtn3 = new DIconButton(dci);
    //定义左键点击事件，Qt::NoModifier代表无其他修饰键被按下
    QMouseEvent mouseEvent( QEvent::MouseButtonPress, QPoint(1,1), Qt::LeftButton , Qt::LeftButton, Qt::NoModifier );
    QApplication::sendEvent(iconBtn3,&mouseEvent);
    layout->addRow(addBtnRow(iconBtn3, "pressed state"));

//    DIconButton *iconBtn4 = new DIconButton(dci);
    //定义左键点击事件，Qt::NoModifier代表无其他修饰键被按下
//    QMouseEvent mouseEvent2( QEvent::MouseTrackingChange, QPoint(1,1), Qt::LeftButton, Qt::LeftButton,Qt::NoModifier );
//    QApplication::sendEvent(iconBtn3,&mouseEvent2);
//    iconBtn4->setAttribute(Qt::WA_Hover,true);
//    QPalette p1 = iconBtn4->palette();
//    p1.setColor(QPalette::Highlight, makeColor QPalette::Highlight+10);
//    iconBtn4->setPalette(p1);
//    iconBtn4->setProperty("hovered",true);

//    emit DIconButton::hoveredChanged();
//    layout->addRow(addBtnRow(iconBtn4, "hover state"));

//    QHBoxLayout *hlayout2 = new QHBoxLayout();
//    QLabel *iconLabel = new QLabel();
//    iconLabel->setPixmap(dci.pixmap(1.0, 32, DDciIcon::Light, DDciIcon::Pressed, ));
//    hlayout2->addWidget(iconLabel);
//    hlayout2->addWidget(new QLabel("icon"));
//    layout->addRow(hlayout2);

    win.setCentralWidget(&w);
    win.resize(200,100);
    win.show();
    Dtk::Widget::moveToCenter(&win);
    return a.exec();
}
