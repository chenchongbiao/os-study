#include <QDebug>
#include <DSwitchButton>
#include <QToolButton>
#include <QDir>
#include <QSqlQuery>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>

#include "widget.h"
#include "ui_widget.h"
#include "mapper/containermapper.h"

widget::widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget)
{
    ui->setupUi(this);
    initDB();
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

    contaierId = new DLabel("ID");
    contaierId->setAlignment(Qt::AlignCenter);
    contaierId->setFixedWidth(110);
    columnLayout->addWidget(contaierId);

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
    image->setFixedWidth(150);
    columnLayout->addWidget(image);

    port = new DLabel("端口");
    port->setAlignment(Qt::AlignCenter);
    port->setFixedWidth(90);
    columnLayout->addWidget(port);

    /*
     * 初始化docker列表
    */
    QSqlQuery query =containerMapper.GetContainerList();
    while(query.next()){
        QWidget *dockerWidget = new QWidget(ui->dockerListWdg);  // 主页软件单条数据控件
        dockerWidget->resize(ui->dockerListWdg->width(),ui->dockerListWdg->height());

        QHBoxLayout *layout = new QHBoxLayout(dockerWidget);
        layout->setContentsMargins(0, 0, 0, 0);  //  设置左侧、顶部、右侧和底部边距，

        QRadioButton *checkBtn = new QRadioButton(ui->dockerListWdg);
        checkBtn->setFixedSize(height-20,height);
        layout->addWidget(checkBtn);

        QString id= query.value(0).toString().left(12);
        DLabel *dockerId = new DLabel(id);
        dockerId->setAlignment(Qt::AlignCenter);
        dockerId->setFixedWidth(110);
        layout->addWidget(dockerId);

        QString name = query.value(1).toString();
        DLabel *dockerName = new DLabel(name);
//        dockerName->setAlignment(Qt::AlignCenter);
        dockerName->setFixedWidth(110);
        layout->addWidget(dockerName);

        QString state = query.value(2).toString();
        DSwitchButton *statusBtn = new DSwitchButton();
        if (state == "running"){
            statusBtn->setChecked(true);
        }
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

        QString image = query.value(3).toString();
        if (image.indexOf("sha256") != -1) {
            image = image.mid(7,image.length()-1);
        }
        DLabel *dockerImage = new DLabel(image);
//        dockerImage->setAlignment(Qt::AlignCenter);
        dockerImage->setFixedWidth(150);
        layout->addWidget(dockerImage);

        QByteArray portArray = query.value(4).toString().toUtf8();
        QString port = GetPortFromJson(portArray);
        DLabel *dockerPort = new DLabel(port);
        dockerPort->setAlignment(Qt::AlignCenter);
        dockerPort->setFixedWidth(90);
        layout->addWidget(dockerPort);


        QListWidgetItem *containerItem=new QListWidgetItem(ui->dockerListWdg);
        containerItem->setSizeHint(QSize(40,40));
    //        WContainerItem->setToolTip(); // 提示框
        containerItem->setFlags(Qt::ItemIsSelectable); // 取消选择项
        ui->dockerListWdg->setItemWidget(containerItem,dockerWidget);  // 将dockerWidgetr赋予containerItem
    }
}


void widget::initDB()
{
    //检测已连接的方式 - 默认连接名
    QString dbusDockerDir = QDir::homePath()+"/.config/dbus-docker/data/db.sqlite";
    qDebug() <<dbusDockerDir;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
        db = QSqlDatabase::database("qt_sql_default_connection");
    else
        db = QSqlDatabase::addDatabase("QSQLITE");
    //设置数据库路径，不存在则创建
    db.setDatabaseName(dbusDockerDir);

    //打开数据库
    if(db.open()){
        qDebug()<<"数据库打开成功";
        //关闭数据库
//        db.close();
    }
}

QString widget::GetPortFromJson(QByteArray portArray)
{
    QString result;
    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(portArray, &jsonError);  // 转化为 JSON 文档
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError)) { // 解析未发生错误
        if (doucment.isArray()) { // JSON 文档为数组
                QJsonArray array = doucment.array();
                int nSize = array.size();
                for (int i = 0; i < nSize; ++i) {
                    QJsonValue value = array.at(i);      // 取出单个json
                    QJsonObject obj = value.toObject();  // 转换为object
                    double privatePort =obj.value("PrivatePort").toDouble();
                    double publicPort = obj.value("PublicPort").toDouble();
//                    QString portValue = obj.value("PrivatePort").toString() + obj.value("PublicPort").toString();
//                    QString portValue = QString("%1:%2").arg(privatePort).arg(publicPort);
                    result += QString("%1:%2\n").arg(privatePort).arg(publicPort);
                }
            }
    }
    return result;
}
