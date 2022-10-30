#include <QtConcurrent>
#include <QTimer>
#include <QProcess>
#include <sstream>
#include <math.h>
#include <unistd.h>

#include "widget.h"
#include "ui_widget.h"
#include "waterprogress.h"
#include "utils.h"

#define MB (1024 * 1024)
#define KB (1024)

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    initUI();
//    QtConcurrent::run(,)

    QTimer *timer = new QTimer(this);
    timer->start(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateWaterProgress()));

    connect(loadStatusWp->getTimer(), SIGNAL(timeout()), this, SLOT(computerLoad()));  // 计算负载均衡状态
    connect(cpuStatusWp->getTimer(), SIGNAL(timeout()), this, SLOT(getCPU()));
    connect(memStatusWp->getTimer(), SIGNAL(timeout()), this, SLOT(getMemory()));
    connect(diskStatusWp->getTimer(), SIGNAL(timeout()), this, SLOT(getDisk()));

    process = new QProcess(this);
    connect(process, SIGNAL(readyRead()), this, SLOT(ReadData()));


}

Widget::~Widget()
{
    delete ui;
}

void Widget::updateWaterProgress()
{
//    QtConcurrent::run()QtConcurrent
    loadStatusWp->setValue(loadPercent);

//    cpuPercent = computerCpu();  // 计算CPU使用率
//    cpuStatusWp->setValue(cpuPercent);
    cpuStatusWp->setValue(cpuPercent);
    memStatusWp->setValue(memoryPercent);
    ui->memory_space->setText(QString("%1MB/%2MB").arg(memoryUse).arg(memoryAll));
    diskStatusWp->setValue(diskPercent);
    ui->disk_space->setText(QString("%1GB/%2GB").arg(diskUse).arg(diskAll));


}

void Widget::setLoad(float load)
{
     this->load = load;
}

/*!
 * \brief Widget::getLoad
 * 获取1分钟的负载均衡的结果
 */
float Widget::getLoad()
{
    return load;
}

void Widget::setCpuNum(int cpuNum)
{
    this->cpuNum = cpuNum;
}

int Widget::getCpuNum()
{
    return cpuNum;
}

void Widget::setCpuPercent(int cpuPercent)
{
    this->cpuPercent = cpuPercent;
}

int Widget::getCpuPercent()
{
    return cpuPercent;
}

void Widget::getCPU()
{
    if (process->state() == QProcess::NotRunning) {
        totalNew = idleNew = 0;
        process->start("cat /proc/stat");
    }
}

void Widget::getMemory()
{
    if (process->state() == QProcess::NotRunning) {
        process->start("cat /proc/meminfo");
    }
}

void Widget::getDisk()
{
    if (process->state() == QProcess::NotRunning) {
        process->start("df -h");
    }
}

void Widget::getSystemInfo()
{
    issue = Utils::exec("cat /etc/issue").remove(" \\n").remove("\\l");  // 发行版
    ip = Utils::exec("hostname -I").split(" ").at(0);
    architecture = Utils::exec("uname -m");
}
/*!
 * \brief Widget::computerLoad
 * 计算负载状态
 */
void Widget::computerLoad()
{
    load = Utils::exec("uptime | awk -F 'average: ' '{print $2}' | awk -F ',' '{print $1}'").toFloat();  // 获取负载均衡数据
    // 算法来自宝塔，因为水球的数值为整形，最后做了转换
    loadPercent = (int)round(load / (cpuNum * 2) * 100);
    if (loadPercent > 100)
    {
        loadPercent = 100;
    }
    if (loadPercent <= 30)
    {
        ui->load_status_info->setText("运行流畅");
    }
    if (loadPercent > 30 && loadPercent <= 70)
    {
        ui->load_status_info->setText("运行正常");
    }
    if (loadPercent > 70 && loadPercent <= 90)
    {
        ui->load_status_info->setText("运行缓慢");
    }
    if (loadPercent > 90)
    {
        ui->load_status_info->setText("运行堵塞");
    }
}

void Widget::computerCpu()
{
    /** cat /proc/stat 文件第一行记录分别对应
        cpu  4109938 189 1846825 35332362 22372 0 236920 0 0 0

        user 从系统启动开始累计到当前时刻，用户态的CPU时间，不包含nice值为负进程。
        nice 从系统启动开始累计到当前时刻，nice值为负的进程所占用的CPU时间
        system 从系统启动开始累计到当前时刻，核心时间
        idle 从系统启动开始累计到当前时刻，除IO等待时间以外其它等待时间
        iowait 从系统启动开始累计到当前时刻，IO等待时间
        irq 从系统启动开始累计到当前时刻，硬中断时间
        softirq 从系统启动开始累计到当前时刻，软中断时间

        CPU利用率 = 1 - （CPU空闲时间片 / CPU时间片总和）。
        CPU时间片总和 = user + nice + system + idle + iowait + irq + softirq
        CPU 空闲时间片 = idle
    */
//    cpuUsage = (int)100*(cpuInfo[2].toFloat()+cpuInfo[3].toFloat()+cpuInfo[4].toFloat())/(cpuInfo[2].toFloat()+cpuInfo[3].toFloat()+cpuInfo[4].toFloat()+cpuInfo[5].toFloat());
//    qDebug() << cpuUsage;

//    QString cpuInfo = Utils::exec("cat /proc/stat");
//    QStringList cpuInfoList = cpuInfo.split('\n');
//    QStringList tmpList;
//    for(int i=0;i<3;i++)
//    {
//        tmpList = cpuInfoList.at(i).split(QRegExp("\\s+"), QString::SkipEmptyParts);//按一个或多个空格分割
//        if(i==0)//计算CPU使用率
//        {
//            cpuUsage = (int)100*(tmpList.at(0).toFloat()+tmpList.at(1).toFloat()+tmpList.at(2).toFloat())/(tmpList.at(0).toFloat()+tmpList.at(1).toFloat()+tmpList.at(2).toFloat()+tmpList.at(3).toFloat());
////            qDebug() << tmpList.at(0).toFloat()<< " " << tmpList.at(1).toFloat() << " " << tmpList.at(2).toFloat() << "cpu使用率\n";
////            qDebug() << tmpList.at(0).toFloat()<< " " << tmpList.at(1).toFloat() << " " << tmpList.at(2).toFloat() << " " << tmpList.at(3).toFloat() << "cpu使用率\n";
//        }
//    }
    QStringList list = Utils::exec("cat /proc/stat | grep 'cpu  '").split(" ");
    idleNew = list.at(5).toInt();
    foreach (QString value, list) {
        totalNew += value.toInt();
    }
    int total = totalNew - totalOld;
    int idle = idleNew - idleOld;
    cpuPercent = 100 * (total - idle) / total;
    totalOld = totalNew;
    idleOld = idleNew;
}

void Widget::ReadData()
{
    QtConcurrent::run([=](){
        while (!process->atEnd()) {
            QString s = QLatin1String(process->readLine());
            if (s.startsWith("cpu")) {
                QStringList list = s.split(" ");
                idleNew = list.at(5).toInt();
                foreach (QString value, list) {
                    totalNew += value.toInt();
                }

                int total = totalNew - totalOld;
                int idle = idleNew - idleOld;
                cpuPercent = 100 * (total - idle) / total;
                totalOld = totalNew;
                idleOld = idleNew;
                break;
            } else if (s.startsWith("MemTotal")) {
                s = s.replace(" ", "");
                s = s.split(":").at(1);
                memoryAll = s.left(s.length() - 3).toInt() / KB;
            } else if (s.startsWith("MemFree")) {
                s = s.replace(" ", "");
                s = s.split(":").at(1);
                memoryFree = s.left(s.length() - 3).toInt() / KB;
    //            qDebug() << "MemFree " << memoryFree << endl;
            } else if (s.startsWith("Buffers")) {
                s = s.replace(" ", "");
                s = s.split(":").at(1);
                memoryFree += s.left(s.length() - 3).toInt() / KB;
    //            qDebug() << "Buffers " << memoryFree << endl;
            } else if (s.startsWith("Cached")) {
                s = s.replace(" ", "");
                s = s.split(":").at(1);
                memoryFree += s.left(s.length() - 3).toInt() / KB;
                memoryUse = memoryAll - memoryFree;
                memoryPercent = 100 * memoryUse / memoryAll;
                break;
            } else if (s.startsWith("/dev/sda") | s.startsWith("/dev/nvme")) {
                QStringList list = s.split(" ");
                diskUse = list.at(4).left(list.at(4).length() - 1).toInt();
                diskAll = list.at(2).left(list.at(2).length() - 1).toInt();
                diskPercent = list.at(9).left(list.at(9).length() - 1).toInt();
    //            qDebug() << QString("diskUse %1 diskAll %2 diskPercent %3").arg(diskUse).arg(diskAll).arg(diskPercent);
            }
        }
    });
}

void Widget::initUI()
{
    cpuNum = Utils::exec("cpufreq-info | grep 'analyzing CPU'").split("\n").size();  // CPU个数固定，不重复计算)
    ui->cpu_core_num->setText(QString("%1核心").arg(cpuNum));
    getSystemInfo();  // 获取系统信息
    ui->system_info->setText(QString("系统：%1 %2   网络：%3").arg(issue).arg(architecture).arg(ip));
    loadStatusWp = new WaterProgress(ui->load_status,1000);
    cpuStatusWp = new WaterProgress(ui->cpu_status,1000);
    memStatusWp = new WaterProgress(ui->memory_status,300);
    diskStatusWp = new WaterProgress(ui->disk_status,500);

    updateWaterProgress();
}
