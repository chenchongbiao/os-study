#include <DWaterProgress>
#include <QTimer>

#include "waterprogress.h"

WaterProgress::WaterProgress(QWidget *parent,int msec) :
    DWaterProgress(parent)
{
    this->setFixedSize(100,100);
    this->start();

    timer = new QTimer(this);
    timer->setInterval(msec);
    timer->start(msec);
}

WaterProgress::~WaterProgress()
{
//    delete ui;
}

QTimer* WaterProgress::getTimer()
{
    return timer;
}
