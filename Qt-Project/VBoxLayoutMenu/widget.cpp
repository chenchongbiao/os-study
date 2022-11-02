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
    // 顶部菜单
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


    // 左侧菜单
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
//    leftMenuWidgetLayout->setContentsMargins(11, 11, 11, 11);

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
        btn->setStyleSheet("color: #FFFFFF;  background-color: #0081ff; border-radius: 8; border: 0px; height: 35px;");
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

    // 右侧菜单
    int rightMenuBtnWidth = 125;
    int rightMenuHeight = 35;

    rightMenuWidget = new QWidget(ui->right_menu);
    rightMenuWidget->resize(140,330);
    rightMenuWidgetLayout = new QVBoxLayout(rightMenuWidget);
    rightMenuWidgetLayout->setSpacing(6);  // 上下控件距离

    rbt1 = new QPushButton(rightMenuWidget);
    rbt1->setText("首页");
    rbt1->resize(rightMenuBtnWidth,rightMenuHeight);
    rightMenuWidgetLayout->addWidget(rbt1);

    rbt2 = new QPushButton(rightMenuWidget);
    rbt2->setText("Docker");
    rightMenuWidgetLayout->addWidget(rbt2);

    rbt3 = new QPushButton(rightMenuWidget);
    rbt3->setText("Ftp");
    rightMenuWidgetLayout->addWidget(rbt3);

    rbt4 = new QPushButton(rightMenuWidget);
    rbt4->setText("数据库");
    rightMenuWidgetLayout->addWidget(rbt4);

    rbt5 = new QPushButton(rightMenuWidget);
    rbt5->setText("编程环境");
    rightMenuWidgetLayout->addWidget(rbt5);

    rbt6 = new QPushButton(rightMenuWidget);
    rbt6->setText("软件安装");
    rightMenuWidgetLayout->addWidget(rbt6);

    rbt7 = new QPushButton(rightMenuWidget);
    rbt7->setText("设置");
    rightMenuWidgetLayout->addWidget(rbt7);

    rightMenuList << rbt1 << rbt2 << rbt3 << rbt4 << rbt5 << rbt6 << rbt7;
    for (int i=0;i < leftMenuList.count();i++)
    {
        QPushButton *btn = rightMenuList.at(i);
        btn->setStyleSheet("border-radius: 8; border: 0px;");

        connect(btn, &MenuButton::clicked, this, [=](){
            QPushButton *curBtn = (QPushButton *)sender();  // 槽函数中调用sender函数，返回指向发送信号的对象的指针
            qDebug() << "当前按下" << curBtn->text();
            for (int i = 0; i < rightMenuList.count(); i++) {
                QPushButton *btn = rightMenuList.at(i);
                if (curBtn == btn)
                {
                    btn->setStyleSheet("color: #FFFFFF;  background-color: #0081ff; border-radius: 8; border: 0px;height: 35px;");
                } else {
                    btn->setStyleSheet("color: #252525; border-radius: 8; border: 0px;");
                }
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
