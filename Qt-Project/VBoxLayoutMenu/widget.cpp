#include <QWidget>
#include <QDebug>

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    initUI();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initUI()
{
    const int width = 90;
    const int height = 50;
    QColor normalTextColor = QColor("#252525");
    QColor checkTextColor = QColor("#FFFFFF");

    QColor normalBgColor = QColor("#FFFFFF");
    QColor checkBgColor = QColor("#0081ff");

    menuWidget = new QWidget(ui->menuWidget);
    menuWidget->resize(730,50);
    menuWidgetLayout = new QHBoxLayout(menuWidget);
    menuWidgetLayout->setSpacing(10);
    menuWidgetLayout->setContentsMargins(0, 0, 0, 0);

    btn1 = new MenuButton(menuWidget);
    btn1->setText("容器列表");
    btn1->resize(width,height);
    menuWidgetLayout->addWidget(btn1);

    btn2 = new MenuButton(menuWidget);
    btn2->setText("镜像管理");
    btn2->resize(width,height);
    menuWidgetLayout->addWidget(btn2);

    btn3 = new MenuButton(menuWidget);
    btn3->setText("镜像导出");
    btn3->resize(width,height);
    menuWidgetLayout->addWidget(btn3);

    btn4 = new MenuButton(menuWidget);
    btn4->setText("仓库");
    btn4->resize(width,height);
    menuWidgetLayout->addWidget(btn4);

    menuList << btn1 << btn2 << btn3 << btn4;
    for (int i=0;i < menuList.count();i++)
    {
        MenuButton *btn = menuList.at(i);
        btn->setPaddingLeft(0);
        btn->setTextAlign(MenuButton::TextAlign_Center);
        btn->setLinePosition(MenuButton::LinePosition_Top);

        btn->setNormalBgColor(normalBgColor);
        btn->setCheckBgColor(checkBgColor);

        btn->setNormalTextColor(normalTextColor);
        btn->setCheckTextColor(checkTextColor);

        connect(btn, SIGNAL(clicked(bool)), this, SLOT(buttonClick()));
    }

    btn1->setChecked(true);
}


void Widget::buttonClick()
{
    MenuButton *curBtn = (MenuButton *)sender();  // 槽函数中调用sender函数，返回指向发送信号的对象的指针
    qDebug() << "当前按下" << curBtn->text();
    for (int i = 0; i < menuList.count(); i++) {
        MenuButton *btn = menuList.at(i);
        btn->setChecked(curBtn == btn);
    }
}
