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
    menuWidget = new QWidget(this);
    menuWidgetLayout = new QHBoxLayout(menuWidget);
    menuWidgetLayout->setSpacing(6);
    menuWidgetLayout->setContentsMargins(11, 11, 11, 11);

    btn1 = new MenuButton(menuWidget);
    btn1->resize(106, 36);
    btn1->setText("容器列表");
    menuWidgetLayout->addWidget(btn1);

    btn2 = new MenuButton(menuWidget);
    btn2->resize(106, 36);
    btn2->setText("镜像管理");
    menuWidgetLayout->addWidget(btn2);

    btn3 = new MenuButton(menuWidget);
    btn3->resize(106, 36);
    btn3->setText("镜像导出");
    menuWidgetLayout->addWidget(btn3);

    menuList << btn1 << btn2 << btn3;

    for (int i=0;i < menuList.count();i++)
    {
        MenuButton *btn = menuList.at(i);
        connect(btn, SIGNAL(clicked(bool)), this, SLOT(buttonClick()));
    }
}


void Widget::buttonClick()
{
    MenuButton *b = (MenuButton *)sender();
    qDebug() << "当前按下" << b->text();
    for (int i = 0; i < menuList.count(); i++) {
        MenuButton *btn = menuList.at(i);
        btn->setChecked(b == btn);
    }
}
