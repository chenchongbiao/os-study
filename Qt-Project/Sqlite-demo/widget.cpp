#include <QDebug>
#include <DSwitchButton>
#include <QToolButton>

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

    createBtn = new DPushButton("创建");
    createBtn->setStyleSheet("color: #FFFFFF; background-color: #67C23A; border-radius: 5; border: 0px; height: 35px; width: 90px; font-size:15px;");
    conBtnLayout->addWidget(createBtn);

    /*
        列名初始化
    */

    columnWidget = new QWidget(ui->columnDfrm);
    columnLayout = new QHBoxLayout(columnWidget);
    columnLayout->setContentsMargins(15, 0, 0, 0);  //  设置左侧、顶部、右侧和底部边距，
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

    address = new DLabel("监控");
    address->setAlignment(Qt::AlignCenter);
    address->setFixedWidth(110);
    columnLayout->addWidget(address);

    image = new DLabel("镜像");
    image->setAlignment(Qt::AlignCenter);
    image->setFixedWidth(110);
    columnLayout->addWidget(image);

    port = new DLabel("端口");
    port->setAlignment(Qt::AlignCenter);
    port->setFixedWidth(110);
    columnLayout->addWidget(port);

    ip = new DLabel("IP地址");
    ip->setAlignment(Qt::AlignCenter);
    ip->setFixedWidth(110);
    columnLayout->addWidget(ip);

    /*
     * 初始化docker列表
    */
    for (int i=0;i<6;i++) {
        QWidget *dockerWidget = new QWidget(ui->dockerListWdg);  // 主页软件单条数据控件
        dockerWidget->resize(ui->dockerListWdg->width(),ui->dockerListWdg->height());

        QHBoxLayout *layout = new QHBoxLayout(dockerWidget);
        layout->setContentsMargins(0, 0, 0, 0);  //  设置左侧、顶部、右侧和底部边距，

        QRadioButton *checkBtn = new QRadioButton(ui->dockerListWdg);
        checkBtn->setFixedSize(height-20,height);
        layout->addWidget(checkBtn);

        DLabel *dockerName = new DLabel("/fastosdocker");
        dockerName->setAlignment(Qt::AlignCenter);
        dockerName->setFixedWidth(110);
        layout->addWidget(dockerName);

        DSwitchButton *statusBtn = new DSwitchButton();
        statusBtn->setFixedWidth(60);
        layout->addWidget(statusBtn);

        DLabel *dockerAddress = new DLabel();
        dockerAddress->setAlignment(Qt::AlignCenter);
        dockerAddress->setFixedWidth(110);
        layout->addWidget(dockerAddress);

        QWidget *addressWidget = new QWidget(dockerAddress);
        addressWidget->resize(addressWidget->width(),addressWidget->height());
        QHBoxLayout *addressLayout = new QHBoxLayout(addressWidget);
        addressLayout->setContentsMargins(0, 0, 0, 0);  //  设置左侧、顶部、右侧和底部边距，
        DPushButton *logBtn = new DPushButton(addressWidget);
        logBtn->setFixedSize(20,20);
        logBtn->setIcon(QIcon(":/images/log.svg"));
        logBtn->setStyleSheet("DPushButton{background-color:transparent}");        //背景透明
        addressLayout->addWidget(logBtn);

        DPushButton *terminalBtn = new DPushButton(addressWidget);
        terminalBtn->setFixedSize(20,20);
        terminalBtn->setIcon(QIcon(":/images/terminal.svg"));
        logBtn->setStyleSheet("DPushButton{background-color:transparent}");
        addressLayout->addWidget(terminalBtn);

        DLabel *dockerImage = new DLabel("wangbinxingkong/fa");
        dockerImage->setAlignment(Qt::AlignCenter);
        dockerImage->setFixedWidth(110);
        layout->addWidget(dockerImage);

        DLabel *dockerPort = new DLabel("8081 : 8081\n"
                                        "8082 : 8081");
        dockerPort->setAlignment(Qt::AlignCenter);
        dockerPort->setFixedWidth(110);
        layout->addWidget(dockerPort);

        DLabel *dockerIp = new DLabel("172.17.0.2");
        dockerIp->setAlignment(Qt::AlignCenter);
        dockerIp->setFixedWidth(110);
        layout->addWidget(dockerIp);

        QListWidgetItem *containerItem=new QListWidgetItem(ui->dockerListWdg);
        containerItem->setSizeHint(QSize(40,40));
    //        WContainerItem->setToolTip(); // 提示框
        containerItem->setFlags(Qt::ItemIsSelectable); // 取消选择项
        ui->dockerListWdg->setItemWidget(containerItem,dockerWidget);  // 将dockerWidgetr赋予containerItem
    }
}
