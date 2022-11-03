#include <QDebug>

#include "widget.h"
#include "ui_widget.h"

widget::widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget)
{
    ui->setupUi(this);
    initUI();
}

widget::~widget()
{
    delete ui;
}

void widget::initUI()
{
    /*
        按钮初始化
    */
    int width = ui->conDfrm->width();
    int height = ui->conDfrm->height();
    // 操作按钮布局
    conBtnWidget = new QWidget(ui->conDfrm);
    conBtnWidget->resize(width,height);
    conBtnLayout = new QHBoxLayout(conBtnWidget);
    conBtnLayout->setSpacing(6);  // 部件之间的间距
    conBtnLayout->setContentsMargins(10, 0, 0, 0);  //  设置左侧、顶部、右侧和底部边距，
    conBtnLayout->setAlignment(Qt::AlignLeft);
    conBtnLayout->insertSpacing(0, -12);
    conBtnLayout->addSpacing(10);

    startBtn = new DPushButton("开始");
    startBtn->setStyleSheet("color: #FFFFFF; background-color: #1E90FF; border-radius: 5; border: 0px; height: 35px; width: 90px; font-size:15px;");
    conBtnLayout->addWidget(startBtn);

    stopBtn = new DPushButton("停止");
    stopBtn->setStyleSheet("color: #FFFFFF; background-color: #F56C6C; border-radius: 5; border: 0px; height: 35px; width: 90px; font-size:15px;");
    conBtnLayout->addWidget(stopBtn);

    restartBtn = new DPushButton("重启");
    restartBtn->setStyleSheet("color: #FFFFFF; background-color: #1E90FF; border-radius: 5; border: 0px; height: 35px; width: 90px; font-size:15px;");
    conBtnLayout->addWidget(restartBtn);

    deleteBtn = new DPushButton("删除");
    deleteBtn->setStyleSheet("color: #FFFFFF; background-color: #F56C6C; border-radius: 5; border: 0px; height: 35px; width: 90px; font-size:15px;");
    conBtnLayout->addWidget(deleteBtn);

    cteateBtn = new DPushButton("创建");
    cteateBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; height: 35px; width: 90px; font-size:15px;");
    conBtnLayout->addWidget(cteateBtn);


    /*
        列名初始化
    */

    columnWidget = new QWidget(ui->columnDfrm);
    columnLayout = new QHBoxLayout(columnWidget);
    columnLayout->setContentsMargins(10, 0, 0, 0);  //  设置左侧、顶部、右侧和底部边距，
    columnLayout->setSpacing(0);  // 部件之间的间距

    checkAllBtn = new QRadioButton(columnWidget);
    checkAllBtn->setFixedSize(height-20,height);
    columnLayout->addWidget(checkAllBtn);

    name = new DLabel("容器名");
    name->setAlignment(Qt::AlignCenter);
    name->setFixedWidth(110);
    columnLayout->addWidget(name);

    status = new DLabel("状态");
    status->setAlignment(Qt::AlignCenter);
    status->setFixedWidth(110);
    columnLayout->addWidget(status);

    address = new Dtk::Widget::DLabel("监控");
    address->setAlignment(Qt::AlignCenter);
    address->setFixedWidth(110);
    columnLayout->addWidget(address);

    image = new Dtk::Widget::DLabel("镜像");
    image->setAlignment(Qt::AlignCenter);
    image->setFixedWidth(110);
    columnLayout->addWidget(image);

    port = new Dtk::Widget::DLabel("端口");
    port->setAlignment(Qt::AlignCenter);
    port->setFixedWidth(110);
    columnLayout->addWidget(port);

    ip = new Dtk::Widget::DLabel("IP地址");
    ip->setAlignment(Qt::AlignCenter);
    ip->setFixedWidth(110);
    columnLayout->addWidget(ip);


}
