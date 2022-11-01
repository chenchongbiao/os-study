#ifndef WATERPROGRESS_H
#define WATERPROGRESS_H

#include <QWidget>
#include <DWaterProgress>

DWIDGET_USE_NAMESPACE

class WaterProgress : public DWaterProgress
{
    Q_OBJECT

public:
    explicit WaterProgress(QWidget *parent = nullptr,int msec = 1000);
    ~WaterProgress();

    QTimer *getTimer();
private slots:

private:
    QTimer *timer;               // 绘制定时器
};

#endif // WATERPROGRESS_H
