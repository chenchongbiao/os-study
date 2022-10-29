#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QProcess>

#include "waterprogress.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    void getSystemInfo();      // 获取系统信息
    void setLoad(float load);  // 设置负载值
    float getLoad();           // 获取负载值
    void setCpuNum(int cpuNums);// 设置CPU核心数
    int getCpuNum();            // 获取CPU核心数

private slots:
    void updateWaterProgress(); // 更新进度条
    void computerLoad();         // 计算负载状态
    void computerCpu();          // 计算CPU使用率
    int getCpuPercent();          // 获取CPU使用率
    void setCpuPercent(int cpuUsage); // 设置CPU使用率
    void getCPU();  // 读取/proc/stat数据
    void getMemory();  // 读取/proc/mominfo
    void ReadData();   // 读取内存和CPU数据
    void getDisk();    // 读取磁盘数据
private:
    void initUI();
private:
    Ui::Widget *ui;
    WaterProgress *loadStatusWp;  // 负载状态的进度条
    WaterProgress *cpuStatusWp;   // CPU使用率的进度条
    WaterProgress *memStatusWp;   // 内存使用率进度条
    WaterProgress *diskStatusWp;  // 磁盘使用率进度条
    QString cpuFile="/proc/stat";
    QString memFile="/proc/meminfo";
    QString proFile="/proc";

    float load = 0; // 负载均衡的值
    int cpuNum = 0;  // cpu数量
    int memNum = 0;  // 内存大小
    int loadPercent = 0; // 负载状态的百分比

    int totalNew=0, idleNew=0, totalOld=0, idleOld=0;
    int cpuPercent=0;  // cpu使用率
    int memoryPercent=0;// 内存使用率
    int memoryAll=0;  // 内存总数
    int memoryUse=0;  //  内存使用空间
    int memoryFree=0;  // 空闲内存数

    int diskPercent=0; // 磁盘使用率
    int diskUse=0;  //  磁盘使用空间
    int diskAll=0;  // 磁盘总量

    QString issue;  // 发行版
    QString ip; // ip地址
    QString  architecture;  //架构
    QProcess *process;
};

#endif // WIDGET_H
