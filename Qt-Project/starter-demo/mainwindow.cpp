#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
     QMainWindow(parent),
     ui(new Ui::MainWindow)
{
     ui->setupUi(this);
     //设置窗口大小
     setGeometry(QRect(300,300,480,480));
     //设置窗口背景色
     QPalette palette(this->palette());
     palette.setColor(QPalette::Background, QColor(123,63,52));
     this->setPalette(palette);
     //设置窗口标题
     setWindowTitle("UOS程序启动器");
     //创建9个应用程序启动图标
     for(int i=0;i<3;i++){
         for(int j=0;j<3;j++){
              //创建一个按钮
              QPushButton *button = new QPushButton(this);
              //设置按钮的大小和位置
              button->setGeometry(QRect(50+i*130,50+j*130,120,120));
              //创建一个图标QIcon对象，资源文件路径可以是绝对路径，也可以是导入项目后资源文件的路径
              QIcon icon3D(QPixmap(QString(":/ico/ico/image%1.jpeg").arg(i*3+j+1)).
                      scaled(QSize(119, 119)));
              //设置按钮文字
              button->setText("");
              //设置按钮的图标
              button->setIconSize(QSize(120, 120));
              button->setIcon(icon3D);
              //连接信号和槽：单击按钮退出程序
              connect(button,SIGNAL(clicked()),this,SLOT(close()));
         }
     }
}

MainWindow::~MainWindow()
{
    delete ui;
}
