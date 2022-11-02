#include <QWidget>
#include <QVBoxLayout>
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
    normalBgColor.setAlpha(0);  // 数值越小越透明
    QColor checkBgColor = QColor("#0081ff");

    topMenuWidget = new QWidget(ui->top_menu);
    topMenuWidget->resize(730,50);
    topMenuWidgetLayout = new QHBoxLayout(topMenuWidget);
    topMenuWidgetLayout->setSpacing(10);
    topMenuWidgetLayout->setContentsMargins(0, 0, 0, 0);

    btn1 = new MenuButton(topMenuWidget);
    btn1->setText("容器列表");
    btn1->resize(width,height);
    topMenuWidgetLayout->addWidget(btn1);

    btn2 = new MenuButton(topMenuWidget);
    btn2->setText("镜像管理");
    btn2->resize(width,height);
    topMenuWidgetLayout->addWidget(btn2);

    btn3 = new MenuButton(topMenuWidget);
    btn3->setText("镜像导出");
    btn3->resize(width,height);
    topMenuWidgetLayout->addWidget(btn3);

    btn4 = new MenuButton(topMenuWidget);
    btn4->setText("仓库");
    btn4->resize(width,height);
    topMenuWidgetLayout->addWidget(btn4);

    topMenuList << btn1 << btn2 << btn3 << btn4;
    for (int i=0;i < topMenuList.count();i++)
    {
        MenuButton *btn = topMenuList.at(i);
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



    QFont font;
    font.setFamily(QString::fromUtf8("Zeniq"));
    font.setPointSize(11);
    font.setBold(false);
    font.setItalic(false);
    font.setWeight(50);

    int leftMenuBtnWidth = 125;
    int leftMenuBtnheight = 35;
    leftMenuWidget = new QWidget(ui->left_menu);
    leftMenuWidget->resize(140,330);

    leftMenuWidgetLayout = new QVBoxLayout(leftMenuWidget);
    leftMenuWidgetLayout->setSpacing(6);
    leftMenuWidgetLayout->setContentsMargins(11, 11, 11, 11);

    menuHome = new MenuButton(leftMenuWidget);
    menuHome->setText("首页");
    menuHome->setFont(font);
    menuHome->resize(leftMenuBtnWidth,leftMenuBtnheight);
    leftMenuWidgetLayout->addWidget(menuHome);

    menuDocker = new MenuButton(leftMenuWidget);
    menuDocker->setText("Docker");
    leftMenuWidgetLayout->addWidget(menuDocker);

    menuFtp = new MenuButton(leftMenuWidget);
    menuFtp->setText("Ftp");
    leftMenuWidgetLayout->addWidget(menuFtp);

    menuSql = new MenuButton(leftMenuWidget);
    menuSql->setText("数据库");
    leftMenuWidgetLayout->addWidget(menuSql);

    menuProgram = new MenuButton(leftMenuWidget);
    menuProgram->setText("编程环境");
    leftMenuWidgetLayout->addWidget(menuProgram);

    menuSoftware = new MenuButton(leftMenuWidget);
    menuSoftware->setText("软件安装");
    leftMenuWidgetLayout->addWidget(menuSoftware);

    menuSetting = new MenuButton(leftMenuWidget);
    menuSetting->setText("设置");
    leftMenuWidgetLayout->addWidget(menuSetting);

    leftMenuList << menuHome << menuDocker << menuFtp << menuSql << menuProgram << menuSoftware << menuSetting;
    for (int i=0;i < leftMenuList.count();i++)
    {
        MenuButton *btn = leftMenuList.at(i);
//        btn->setStyleSheet("border: 0px; border-radius: 5; border: 0px;");
        btn->setFlat(true);
        btn->setPaddingLeft(0);
        btn->setTextAlign(MenuButton::TextAlign_Center);
        btn->setLinePosition(MenuButton::LinePosition_Top);

        btn->setNormalBgColor(normalBgColor);
        btn->setCheckBgColor(checkBgColor);

        btn->setNormalTextColor(normalTextColor);
        btn->setCheckTextColor(checkTextColor);

        connect(btn, &MenuButton::clicked, this, [=](){
            MenuButton *curBtn = (MenuButton *)sender();  // 槽函数中调用sender函数，返回指向发送信号的对象的指针
            qDebug() << "当前按下" << curBtn->text();
            for (int i = 0; i < leftMenuList.count(); i++) {
                MenuButton *btn = leftMenuList.at(i);
                btn->setChecked(curBtn == btn);
            }
        });
    }
}


void Widget::buttonClick()
{
    MenuButton *curBtn = (MenuButton *)sender();  // 槽函数中调用sender函数，返回指向发送信号的对象的指针
    qDebug() << "当前按下" << curBtn->text();
    for (int i = 0; i < topMenuList.count(); i++) {
        MenuButton *btn = topMenuList.at(i);
        btn->setChecked(curBtn == btn);
    }
}
